#include "d3d9_vita.h"

#include "vita2d/libvita2d/include/vita2d.h"
#include "vita2d/libvita2d/include/shared.h"

#include <algorithm>
#include <assert.h>

class Direct3D : public IDirect3D9
{
public:
	
	HRESULT CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface) override;
};

class Device : public IDirect3DDevice9
{
public:
	
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

struct Vertex
{
	float position[3];
	D3DCOLOR colour;
	float uv[2];
};

static inline vita2d_color_vertex transform_vertex(const Vertex &src)
{
	vita2d_color_vertex dst;
	dst.x = src.position[0];
	dst.y = src.position[1];
	dst.z = src.position[2];
	dst.color = (src.colour & 0xff00ff00) | ((src.colour & 0xff) << 16) | ((src.colour >> 16) & 0xff);
	
	return dst;
}

IDirect3D9 *Direct3DCreate9(UINT SDKVersion)
{
	vita2d_init();
	
	return new Direct3D;
}

HRESULT Direct3D::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface)
{
	*ppReturnedDeviceInterface = new Device;
	
	return D3D_OK;
}

HRESULT Device::BeginScene()
{
	vita2d_start_drawing();
	
	return D3D_OK;
}

HRESULT Device::Clear(int a, const void *b, int buffers, D3DCOLOR color, float z, int c)
{
	assert(a == 0);
	assert(b == nullptr);
	assert(buffers == (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER));
	assert(color == D3DCOLOR_XRGB(0, 0, 0));
	assert(z == 1);
	assert(c == 0);
	
	vita2d_clear_screen();
	
	return D3D_OK;
}

HRESULT Device::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle)
{
	*ppSurface = nullptr;
	
	return D3D_OK;
}

HRESULT Device::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	assert(VertexStreamZeroStride > 0);
	
	SceGxmPrimitiveType mode = SCE_GXM_PRIMITIVE_TRIANGLES;
	unsigned int vertex_count = 0;
	switch (PrimitiveType)
	{
		case D3DPT_LINELIST:
			mode = SCE_GXM_PRIMITIVE_LINES;
			vertex_count = PrimitiveCount * 2;
			break;
		case D3DPT_TRIANGLELIST:
			mode = SCE_GXM_PRIMITIVE_TRIANGLES;
			vertex_count = PrimitiveCount * 3;
			break;
		case D3DPT_TRIANGLESTRIP:
			mode = SCE_GXM_PRIMITIVE_TRIANGLE_STRIP;
			vertex_count = PrimitiveCount + 2;
			break;
		default:
			assert(!"Unhandled D3DPRIMITIVETYPE.");
			break;
	}
	
	const Vertex *const src_vertices = static_cast<const Vertex *>(pVertexStreamZeroData);
	
	vita2d_color_vertex *const dst_vertices = static_cast<vita2d_color_vertex *>(vita2d_pool_memalign(vertex_count * sizeof(vita2d_color_vertex), sizeof(vita2d_color_vertex)));
	uint16_t *const indices = static_cast<uint16_t *>(vita2d_pool_memalign(vertex_count * sizeof(uint16_t), sizeof(uint16_t)));
	
	std::transform(&src_vertices[0], &src_vertices[vertex_count], &dst_vertices[0], transform_vertex);
	
	for (unsigned int i = 0; i < vertex_count; ++i)
	{
		indices[i] = i;
	}
	
	sceGxmSetVertexProgram(_vita2d_context, _vita2d_colorVertexProgram);
	sceGxmSetFragmentProgram(_vita2d_context, _vita2d_colorFragmentProgram);
	
	void *vertexDefaultBuffer;
	sceGxmReserveVertexDefaultUniformBuffer(_vita2d_context, &vertexDefaultBuffer);
	sceGxmSetUniformDataF(vertexDefaultBuffer, _vita2d_colorWvpParam, 0, 16, _vita2d_ortho_matrix);
	
	sceGxmSetVertexStream(_vita2d_context, 0, dst_vertices);
	sceGxmDraw(_vita2d_context, SCE_GXM_PRIMITIVE_TRIANGLE_STRIP, SCE_GXM_INDEX_FORMAT_U16, indices, vertex_count);
	
	return D3D_OK;
}

HRESULT Device::EndScene()
{
	vita2d_end_drawing();
	
	return D3D_OK;
}

HRESULT Device::GetDeviceCaps(D3DCAPS9 *pCaps)
{
	memset(pCaps, 0, sizeof(*pCaps));
	
	return D3D_OK;
}

HRESULT Device::Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
	assert(pSourceRect == nullptr);
	assert(pDestRect == nullptr);
	assert(hDestWindowOverride == nullptr);
	assert(pDirtyRegion == nullptr);
	
	vita2d_swap_buffers();
	
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
	assert(Level == 0);
	
	memset(pDesc, 0, sizeof(*pDesc));
	pDesc->Width = vita2d_texture_get_width(texture.get());
	pDesc->Height = vita2d_texture_get_height(texture.get());
	
	return D3D_OK;
}

HRESULT Texture::LockRect(UINT Level, D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags)
{
	assert(Level == 0);
	assert(pRect == nullptr);
	
	memset(pLockedRect, 0, sizeof(*pLockedRect));
	pLockedRect->Pitch = vita2d_texture_get_stride(texture.get());
	pLockedRect->pBits = vita2d_texture_get_datap(texture.get());
	
	return D3D_OK;
}

HRESULT Texture::UnlockRect(UINT Level)
{
	return D3D_OK;
}
