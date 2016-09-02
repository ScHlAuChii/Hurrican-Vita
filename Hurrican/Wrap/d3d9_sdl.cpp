#include "d3d9_sdl.h"

#include "SDL_opengl.h"
#include "SDL_video.h"

#include <assert.h>

class Direct3D : public IDirect3D9
{
public:
	
	HRESULT CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface) override;
};

class Device : public IDirect3DDevice9
{
public:
	
	std::vector<uint32_t> colours;
	
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

static inline uint32_t bgra_to_rgba(const Vertex &src)
{
	const uint32_t r = (src.colour >> 16) & 0xff;
	const uint32_t b = (src.colour & 0xff) << 16;
	return (src.colour & 0xff00ff00) | b | r;
}

void check()
{
	assert(glGetError() == GL_NO_ERROR);
}

IDirect3D9 *Direct3DCreate9(UINT SDKVersion)
{
	return new Direct3D;
}

HRESULT Direct3D::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface)
{
	SDL_Window *const window = static_cast<SDL_Window *>(hFocusWindow);
	assert(window != nullptr);
	
	SDL_SetWindowSize(window, pPresentationParameters->BackBufferWidth, pPresentationParameters->BackBufferHeight);
	
	const SDL_GLContext context = SDL_GL_CreateContext(window);
	assert(context != nullptr);
	check();
	
	SDL_GL_SetSwapInterval(1);
	check();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	check();
	
	glEnable(GL_BLEND);
	check();
	
	glEnableClientState(GL_COLOR_ARRAY);
	check();
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	check();
	
	glEnableClientState(GL_VERTEX_ARRAY);
	check();
	
	*ppReturnedDeviceInterface = new Device;
	
	return D3D_OK;
}

HRESULT Device::BeginScene()
{
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
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	check();
	
	return D3D_OK;
}

HRESULT Device::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle)
{
	*ppSurface = nullptr;
	
	return D3D_OK;
}

HRESULT Device::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	assert(PrimitiveType == D3DPT_TRIANGLESTRIP);
	assert(VertexStreamZeroStride > 0);
	
	const GLsizei vertex_count = PrimitiveType + 2;
	const Vertex *const vertices = static_cast<const Vertex *>(pVertexStreamZeroData);
	
	colours.resize(vertex_count);
	std::transform(&vertices[0], &vertices[vertex_count], colours.data(), bgra_to_rgba);
	
	glVertexPointer(3, GL_FLOAT, VertexStreamZeroStride, &vertices[0].position);
	check();
	
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colours.data());
	check();
	
	glTexCoordPointer(2, GL_FLOAT, VertexStreamZeroStride, &vertices[0].uv);
	check();
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertex_count);
	check();
	
	return D3D_OK;
}

HRESULT Device::EndScene()
{
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
	
	SDL_Window *const window = SDL_GL_GetCurrentWindow();
	assert(window != nullptr);
	
	SDL_GL_SwapWindow(window);
	
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
	if (pTexture != nullptr)
	{
		const Texture *const texture = static_cast<const Texture *>(pTexture);
		
		glBindTexture(GL_TEXTURE_2D, texture->texture);
		check();
		
		glEnable(GL_TEXTURE_2D);
		check();
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		check();
	}
	
	return D3D_OK;
}

HRESULT Device::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return D3D_OK;
}

HRESULT Device::SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix)
{
	assert(State == D3DTS_PROJECTION);
	
	glMatrixMode(GL_PROJECTION);
	check();
	
	glLoadMatrixf(&pMatrix->_11);
	check();
	
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
	if (texture != 0)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}
}

HRESULT Texture::GetLevelDesc(UINT Level, D3DSURFACE_DESC *pDesc)
{
	assert(Level == 0);
	
	memset(pDesc, 0, sizeof(*pDesc));
	pDesc->Width = width;
	pDesc->Height = height;
	
	return D3D_OK;
}

HRESULT Texture::LockRect(UINT Level, D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags)
{
	assert(Level == 0);
	assert(pRect == nullptr);
	
	memset(pLockedRect, 0, sizeof(*pLockedRect));
	pLockedRect->Pitch = width * 4;
	pLockedRect->pBits = pixels.get();
	
	return D3D_OK;
}

HRESULT Texture::UnlockRect(UINT Level)
{
	return D3D_OK;
}
