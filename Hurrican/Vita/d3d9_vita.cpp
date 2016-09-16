#include "d3d9_vita.h"

#include "../DX8Graphics.h"
#include "../Logdatei.h"

#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/kernel/sysmem.h>

static const unsigned int SCREEN_W = 960;
static const unsigned int SCREEN_H = 544;

static const uint8_t clear_f[] =
{
#include "shaders/clear_v.h"
};

static const uint8_t clear_v[] =
{
#include "shaders/clear_v.h"
};

static size_t align_mem(size_t size, size_t alignment)
{
	return ((size + (alignment - 1)) / alignment) * alignment;
}

static void *gpu_alloc(SceKernelMemBlockType type, unsigned int size, SceGxmMemoryAttribFlags attribs, SceUID *uid)
{
	void *mem = nullptr;
	
	if (type == SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW)
	{
		size = align_mem(size, 256*1024);
	}
	else
	{
		size = align_mem(size, 4*1024);
	}
	
	*uid = sceKernelAllocMemBlock("gpu_mem", type, size, NULL);
	
	if (sceKernelGetMemBlockBase(*uid, &mem) < 0)
		return NULL;
	
	if (sceGxmMapMemory(mem, size, attribs) < 0)
		return NULL;
	
	return mem;
}

void *vertex_usse_alloc(unsigned int size, SceUID *uid, unsigned int *usse_offset)
{
	void *mem = NULL;
	
	size = align_mem(size, 4096);
	*uid = sceKernelAllocMemBlock("vertex_usse", SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE, size, NULL);
	
	if (sceKernelGetMemBlockBase(*uid, &mem) < 0)
		return NULL;
	if (sceGxmMapVertexUsseMemory(mem, size, usse_offset) < 0)
		return NULL;
	
	return mem;
}

void *fragment_usse_alloc(unsigned int size, SceUID *uid, unsigned int *usse_offset)
{
	void *mem = NULL;
	
	size = align_mem(size, 4096);
	*uid = sceKernelAllocMemBlock("fragment_usse", SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE, size, NULL);
	
	if (sceKernelGetMemBlockBase(*uid, &mem) < 0)
		return NULL;
	if (sceGxmMapFragmentUsseMemory(mem, size, usse_offset) < 0)
		return NULL;
	
	return mem;
}

static void *patcher_host_alloc(void *user_data, unsigned int size)
{
	return malloc(size);
}

static void patcher_host_free(void *user_data, void *mem)
{
	free(mem);
}

class Direct3D : public IDirect3D9
{
public:
	
	HRESULT CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface) override;
};

class Device : public IDirect3DDevice9
{
public:
	
	SceGxmContext *context = nullptr;
	SceGxmRenderTarget *renderTarget = nullptr;
	SceUID fb[2] = { -1, -1 };
	int next_buffer = 0;
	SceGxmColorSurface color_surfaces[2] = {};
	SceGxmSyncObject *sync[2] = { nullptr, nullptr };
	SceGxmDepthStencilSurface depth_stencil_surface = {};
	VERTEX2D *clearVertices = nullptr;
	uint16_t *clearIndices = nullptr;
	
#define SHADER(name) SceGxmVertexProgram *name = nullptr;
#	include "shaders_v.h"
#undef SHADER
	
#define SHADER(name) SceGxmFragmentProgram *name = nullptr;
#	include "shaders_f.h"
#undef SHADER
	
	const SceGxmProgramParameter *clear_color_param = nullptr;
	
	HRESULT BeginScene() override;
	HRESULT Clear(int a, const void *b, int buffers, D3DCOLOR color, float z, int c) override;
	HRESULT CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle) override;
	HRESULT DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride) override;
	HRESULT EndScene() override;
	HRESULT GetDeviceCaps(D3DCAPS9 *pCaps) override;
	HRESULT Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion) override;
	HRESULT Reset(D3DPRESENT_PARAMETERS *pPresentationParameters) override;
	HRESULT SetFVF(DWORD FVF) override;
	HRESULT SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) override;
	HRESULT SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) override;
	HRESULT SetTexture(DWORD Sampler, IDirect3DBaseTexture9 *pTexture) override;
	HRESULT SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) override;
	HRESULT SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix) override;
	HRESULT StretchRect(IDirect3DSurface9 *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, const RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter) override;
	HRESULT TestCooperativeLevel() override;
};

static void display_callback(const void *callback_data)
{
	SceDisplayFrameBuf framebuf = {};
	framebuf.size        = sizeof(SceDisplayFrameBuf);
	framebuf.base        = *static_cast<void *const *>(callback_data);
	framebuf.pitch       = SCREEN_W;
	framebuf.pixelformat = SCE_DISPLAY_PIXELFORMAT_A8B8G8R8;
	framebuf.width       = SCREEN_W;
	framebuf.height      = SCREEN_H;
	sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_NEXTFRAME);
}

IDirect3D9 *Direct3DCreate9(UINT SDKVersion)
{
	return new Direct3D;
}

HRESULT Direct3D::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface)
{
	Protokoll.WriteText("Initialising GXM\n", false);
	
	SceGxmInitializeParams params;
	params.flags = 0;
	params.displayQueueMaxPendingCount = 2;
	params.displayQueueCallback = &display_callback;
	params.displayQueueCallbackDataSize = sizeof(const void *);
	params.parameterBufferSize = (16 * 1024 * 1024);
	
	sceGxmInitialize(&params);
	std::unique_ptr<Device> device(new Device);
	
	SceUID vdmRingBufferUid = -1;
	void *vdmRingBuffer = gpu_alloc(
									SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
									SCE_GXM_DEFAULT_VDM_RING_BUFFER_SIZE,
									SCE_GXM_MEMORY_ATTRIB_READ,
									&vdmRingBufferUid);
	
	SceUID vertexRingBufferUid = -1;
	void *vertexRingBuffer = gpu_alloc(
									   SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
									   SCE_GXM_DEFAULT_VERTEX_RING_BUFFER_SIZE,
									   SCE_GXM_MEMORY_ATTRIB_READ,
									   &vertexRingBufferUid);
	
	SceUID fragmentRingBufferUid = -1;
	void *fragmentRingBuffer = gpu_alloc(
										 SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
										 SCE_GXM_DEFAULT_FRAGMENT_RING_BUFFER_SIZE,
										 SCE_GXM_MEMORY_ATTRIB_READ,
										 &fragmentRingBufferUid);
	
	SceUID fragmentUsseRingBufferUid = -1;
	unsigned int fragmentUsseRingBufferOffset;
	void *fragmentUsseRingBuffer = fragment_usse_alloc(
													   SCE_GXM_DEFAULT_FRAGMENT_USSE_RING_BUFFER_SIZE,
													   &fragmentUsseRingBufferUid,
													   &fragmentUsseRingBufferOffset);
	
	SceGxmContextParams contextParams = {};
	contextParams.hostMem				= malloc(SCE_GXM_MINIMUM_CONTEXT_HOST_MEM_SIZE);
	contextParams.hostMemSize			= SCE_GXM_MINIMUM_CONTEXT_HOST_MEM_SIZE;
	contextParams.vdmRingBufferMem			= vdmRingBuffer;
	contextParams.vdmRingBufferMemSize		= SCE_GXM_DEFAULT_VDM_RING_BUFFER_SIZE;
	contextParams.vertexRingBufferMem		= vertexRingBuffer;
	contextParams.vertexRingBufferMemSize		= SCE_GXM_DEFAULT_VERTEX_RING_BUFFER_SIZE;
	contextParams.fragmentRingBufferMem		= fragmentRingBuffer;
	contextParams.fragmentRingBufferMemSize		= SCE_GXM_DEFAULT_FRAGMENT_RING_BUFFER_SIZE;
	contextParams.fragmentUsseRingBufferMem		= fragmentUsseRingBuffer;
	contextParams.fragmentUsseRingBufferMemSize	= SCE_GXM_DEFAULT_FRAGMENT_USSE_RING_BUFFER_SIZE;
	contextParams.fragmentUsseRingBufferOffset	= fragmentUsseRingBufferOffset;
	
	int err = sceGxmCreateContext(&contextParams, &device->context);
	
	// set up parameters
	SceGxmRenderTargetParams renderTargetParams;
	memset(&renderTargetParams, 0, sizeof(SceGxmRenderTargetParams));
	renderTargetParams.flags			= 0;
	renderTargetParams.width			= SCREEN_W;
	renderTargetParams.height			= SCREEN_H;
	renderTargetParams.scenesPerFrame		= 1;
	renderTargetParams.multisampleMode		= SCE_GXM_MULTISAMPLE_NONE;
	renderTargetParams.multisampleLocations		= 0;
	renderTargetParams.driverMemBlock		= -1; // Invalid UID
	
	// create the render target
	err = sceGxmCreateRenderTarget(&renderTargetParams, &device->renderTarget);
	
	for (int i = 0; i < 2; ++i)
	{
		void *const fb_data = gpu_alloc(SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW, SCREEN_W * SCREEN_H * 4, SCE_GXM_MEMORY_ATTRIB_RW, &device->fb[i]);
		
		err = sceGxmColorSurfaceInit(
									 &device->color_surfaces[i],
									 SCE_GXM_COLOR_FORMAT_A8B8G8R8,
									 SCE_GXM_COLOR_SURFACE_LINEAR,
									 SCE_GXM_COLOR_SURFACE_SCALE_NONE,
									 SCE_GXM_OUTPUT_REGISTER_SIZE_32BIT,
									 SCREEN_W,
									 SCREEN_H,
									 SCREEN_W,
									 fb_data);
		
		err = sceGxmSyncObjectCreate(&device->sync[i]);
	}
	
	const unsigned int alignedWidth = align_mem(SCREEN_W, SCE_GXM_TILE_SIZEX);
	const unsigned int alignedHeight = align_mem(SCREEN_H, SCE_GXM_TILE_SIZEY);
	const unsigned int sampleCount = alignedWidth * alignedHeight;
	const unsigned int depthStrideInSamples = alignedWidth;
	SceUID depthBufferUid = -1;
	void *const depthBufferData = gpu_alloc(
								SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
								SCE_GXM_DEPTHSTENCIL_SURFACE_ALIGNMENT,
								SCE_GXM_MEMORY_ATTRIB_RW,
								&depthBufferUid);
	
	err = sceGxmDepthStencilSurfaceInit(&device->depth_stencil_surface,
										SCE_GXM_DEPTH_STENCIL_FORMAT_S8D24,
										SCE_GXM_DEPTH_STENCIL_SURFACE_TILED,
										depthStrideInSamples,
										depthBufferData,
										nullptr);
	
	const unsigned int patcherBufferSize		= 64*1024;
	const unsigned int patcherVertexUsseSize	= 64*1024;
	const unsigned int patcherFragmentUsseSize	= 64*1024;
	
	// allocate memory for buffers and USSE code
	SceUID patcherBufferUid = -1;
	void *patcherBuffer = gpu_alloc(
									SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
									patcherBufferSize,
									SCE_GXM_MEMORY_ATTRIB_RW,
									&patcherBufferUid);
	
	SceUID patcherVertexUsseUid = -1;
	unsigned int patcherVertexUsseOffset;
	void *patcherVertexUsse = vertex_usse_alloc(
												patcherVertexUsseSize,
												&patcherVertexUsseUid,
												&patcherVertexUsseOffset);
	
	SceUID patcherFragmentUsseUid = -1;
	unsigned int patcherFragmentUsseOffset;
	void *patcherFragmentUsse = fragment_usse_alloc(
													patcherFragmentUsseSize,
													&patcherFragmentUsseUid,
													&patcherFragmentUsseOffset);
	
	Protokoll.WriteText("Creating shader patcher\n", false);
	
	// create a shader patcher
	SceGxmShaderPatcherParams patcherParams;
	memset(&patcherParams, 0, sizeof(SceGxmShaderPatcherParams));
	patcherParams.userData			= NULL;
	patcherParams.hostAllocCallback		= &patcher_host_alloc;
	patcherParams.hostFreeCallback		= &patcher_host_free;
	patcherParams.bufferAllocCallback	= NULL;
	patcherParams.bufferFreeCallback	= NULL;
	patcherParams.bufferMem			= patcherBuffer;
	patcherParams.bufferMemSize		= patcherBufferSize;
	patcherParams.vertexUsseAllocCallback	= NULL;
	patcherParams.vertexUsseFreeCallback	= NULL;
	patcherParams.vertexUsseMem		= patcherVertexUsse;
	patcherParams.vertexUsseMemSize		= patcherVertexUsseSize;
	patcherParams.vertexUsseOffset		= patcherVertexUsseOffset;
	patcherParams.fragmentUsseAllocCallback	= NULL;
	patcherParams.fragmentUsseFreeCallback	= NULL;
	patcherParams.fragmentUsseMem		= patcherFragmentUsse;
	patcherParams.fragmentUsseMemSize	= patcherFragmentUsseSize;
	patcherParams.fragmentUsseOffset	= patcherFragmentUsseOffset;
	
	SceGxmShaderPatcher *shaderPatcher = nullptr;
	err = sceGxmShaderPatcherCreate(&patcherParams, &shaderPatcher);
	
#define SHADER(name) \
const SceGxmProgram *const name##_gxp = reinterpret_cast<const SceGxmProgram *>(name); \
SceGxmShaderPatcherId name##_id = nullptr; \
sceGxmShaderPatcherRegisterProgram(shaderPatcher, name##_gxp, &name##_id);
#	include "shaders.h"
#undef SHADER
	
	SceGxmBlendInfo blend_info = {};
	blend_info.colorFunc = SCE_GXM_BLEND_FUNC_ADD;
	blend_info.alphaFunc = SCE_GXM_BLEND_FUNC_ADD;
	blend_info.colorSrc  = SCE_GXM_BLEND_FACTOR_SRC_ALPHA;
	blend_info.colorDst  = SCE_GXM_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	blend_info.alphaSrc  = SCE_GXM_BLEND_FACTOR_ONE;
	blend_info.alphaDst  = SCE_GXM_BLEND_FACTOR_ZERO;
	blend_info.colorMask = SCE_GXM_COLOR_MASK_ALL;
	
	Protokoll.WriteText("Finding parameters.\n", false);

	const SceGxmProgramParameter *const clear_pos_param = sceGxmProgramFindParameterByName(clear_v_gxp, "aPosition");
	const unsigned int clear_pos_index = sceGxmProgramParameterGetResourceIndex(clear_pos_param);
	
	Protokoll.WriteText("Setting up attributes and streams.\n", false);
	
	SceGxmVertexAttribute vertex_attrs[3] = {};
	vertex_attrs[0].streamIndex	= 0;
	vertex_attrs[0].offset		= offsetof(VERTEX2D, x);
	vertex_attrs[0].format		= SCE_GXM_ATTRIBUTE_FORMAT_F32;
	vertex_attrs[0].componentCount	= 2;
	vertex_attrs[0].regIndex = clear_pos_index;
	
	SceGxmVertexStream vertex_stream = {};
	vertex_stream.stride = sizeof(VERTEX2D);
	vertex_stream.indexSource = SCE_GXM_INDEX_SOURCE_INDEX_16BIT;
	
	Protokoll.WriteText("Creating vertex programs.\n", false);
	
	err = sceGxmShaderPatcherCreateVertexProgram(
												 shaderPatcher,
												 clear_v_id,
												 vertex_attrs,
												 1,
												 &vertex_stream,
												 1,
												 &device->clear_v);
	
	Protokoll.WriteText("Creating fragment programs.\n", false);
	
	err = sceGxmShaderPatcherCreateFragmentProgram(
												   shaderPatcher,
												   clear_f_id,
												   SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4,
												   SCE_GXM_MULTISAMPLE_NONE,
												   NULL,
												   clear_v_gxp,
												   &device->clear_f);
	
	Protokoll.WriteText("Creating vertices.\n", false);
	
	// create the clear triangle vertex/index data
	SceUID clearVerticesUid = -1;
	device->clearVertices = (VERTEX2D *)gpu_alloc(
													 SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
													 3*sizeof(VERTEX2D),
													 SCE_GXM_MEMORY_ATTRIB_READ,
													 &clearVerticesUid);
	
	SceUID clearIndicesUid = -1;
	device->clearIndices = (uint16_t *)gpu_alloc(
										 SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE,
										 3*sizeof(uint16_t),
										 SCE_GXM_MEMORY_ATTRIB_READ,
										 &clearIndicesUid);
	
	device->clearVertices[0].x = -1.0f;
	device->clearVertices[0].y = -1.0f;
	device->clearVertices[1].x =  3.0f;
	device->clearVertices[1].y = -1.0f;
	device->clearVertices[2].x = -1.0f;
	device->clearVertices[2].y =  3.0f;
	
	device->clearIndices[0] = 0;
	device->clearIndices[1] = 1;
	device->clearIndices[2] = 2;
	
	Protokoll.WriteText("Finding uniforms.\n", false);
	
	device->clear_color_param = sceGxmProgramFindParameterByName(clear_f_gxp, "uClearColor");
	
	Protokoll.WriteText("Device created!\n\n", false);
	
	*ppReturnedDeviceInterface = device.release();
	
	return D3D_OK;
}

HRESULT Device::BeginScene()
{
	Protokoll.WriteText("BeginScene\n", false);
	
	sceGxmBeginScene(
				  context,
				  0,
				  renderTarget,
				  NULL,
				  NULL,
				  sync[1 - next_buffer],
				  &color_surfaces[next_buffer],
				  &depth_stencil_surface);
	
	return D3D_OK;
}

HRESULT Device::Clear(int a, const void *b, int buffers, D3DCOLOR color, float z, int c)
{
	Protokoll.WriteText("Clear\n", false);
	
	const float clear_color[4] = { 0.25f, 0.5f, 1, 1 };
	
	sceGxmSetVertexProgram(context, clear_v);
	
	Protokoll.WriteText("1\n", false);
	sceGxmSetFragmentProgram(context, clear_f);
	
	Protokoll.WriteText("2\n", false);
	
	void *color_buffer = nullptr;
	sceGxmReserveFragmentDefaultUniformBuffer(context, &color_buffer);
	
	Protokoll.WriteText("3\n", false);
	Protokoll.WriteValue((int)color_buffer);
	Protokoll.WriteValue((int)clear_color_param);
	
	sceGxmSetUniformDataF(color_buffer, clear_color_param, 0, 4, clear_color);
	
	Protokoll.WriteText("4\n", false);
	
	sceGxmSetVertexStream(context, 0, clearVertices);
	Protokoll.WriteText("5\n", false);
	
	sceGxmDraw(context, SCE_GXM_PRIMITIVE_TRIANGLES, SCE_GXM_INDEX_FORMAT_U16, clearIndices, 3);
	
	Protokoll.WriteText("Clear OK\n", false);
	
	return D3D_OK;
}

HRESULT Device::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle)
{
	*ppSurface = nullptr;
	
	return D3D_OK;
}

HRESULT Device::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return D3D_OK;
}

HRESULT Device::EndScene()
{
	Protokoll.WriteText("EndScene\n", false);
	
	sceGxmEndScene(context, NULL, NULL);
	
	return D3D_OK;
}

HRESULT Device::GetDeviceCaps(D3DCAPS9 *pCaps)
{
	memset(pCaps, 0, sizeof(*pCaps));
	
	return D3D_OK;
}

HRESULT Device::Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
	Protokoll.WriteText("Present\n", false);
	
	void *base = nullptr;
	sceKernelGetMemBlockBase(fb[next_buffer], &base);
	sceGxmPadHeartbeat(&color_surfaces[next_buffer], sync[next_buffer]);
	sceGxmDisplayQueueAddEntry(
							   sync[1 - next_buffer],	// OLD fb
							   sync[next_buffer],	// NEW fb
							   &base);
	
	next_buffer = 1 - next_buffer;
	
	return D3D_OK;
}

HRESULT Device::Reset(D3DPRESENT_PARAMETERS *pPresentationParameters)
{
	return D3D_OK;
}

HRESULT Device::SetFVF(DWORD FVF)
{
	return D3D_OK;
}

HRESULT Device::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return D3D_OK;
}

HRESULT Device::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return D3D_OK;
}

HRESULT Device::SetTexture(DWORD Sampler, IDirect3DBaseTexture9 *pTexture)
{
	return D3D_OK;
}

HRESULT Device::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return D3D_OK;
}

HRESULT Device::SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix)
{
	return D3D_OK;
}

HRESULT Device::StretchRect(IDirect3DSurface9 *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, const RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return D3D_OK;
}

HRESULT Device::TestCooperativeLevel()
{
	return D3D_OK;
}

Texture::~Texture()
{
}

HRESULT Texture::GetLevelDesc(UINT Level, D3DSURFACE_DESC *pDesc)
{
	memset(pDesc, 0, sizeof(*pDesc));
	pDesc->Width = width;
	pDesc->Height = height;
	
	return D3D_OK;
}

HRESULT Texture::LockRect(UINT Level, D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags)
{
	memset(pLockedRect, 0, sizeof(*pLockedRect));
	pLockedRect->Pitch = width * 4;
	pLockedRect->pBits = pixels.get();
	
	return D3D_OK;
}

HRESULT Texture::UnlockRect(UINT Level)
{
	return D3D_OK;
}
