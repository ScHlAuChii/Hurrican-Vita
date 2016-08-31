#include "d3dx9.h"

#include "d3d9_sdl.h"

#include "SDL_surface.h"

#include <assert.h>
#include <memory>

typedef std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *)> SurfacePtr;
typedef std::unique_ptr<Texture> TexturePtr;

HRESULT D3DXCreateTextureFromFileEx(LPDIRECT3DDEVICE9 pDevice, LPCTSTR pSrcFile, UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT          Format, D3DPOOL Pool, DWORD Filter, DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY       *pPalette, LPDIRECT3DTEXTURE9 *ppTexture)
{
	assert(pDevice != nullptr);
	assert(Width == 0);
	assert(Height == 0);
	assert(MipLevels == 1);
	assert(Usage == 0);
	assert(Format == D3DFMT_UNKNOWN);
	assert(Pool == D3DPOOL_MANAGED);
	assert(Filter == D3DX_FILTER_NONE);
	assert(MipFilter == D3DX_FILTER_NONE);
	assert(ColorKey == D3DCOLOR_XRGB(255, 0, 255));
	assert(pSrcInfo == nullptr);
	assert(pPalette == nullptr);
	assert(ppTexture != nullptr);
	
	*ppTexture = nullptr;
	
	const SurfacePtr surface(SDL_LoadBMP(pSrcFile), &SDL_FreeSurface);
	assert(surface);
	
	TexturePtr texture(new Texture);
	texture->width = surface->w;
	texture->height = surface->h;
	texture->pixels.resize(surface->w * surface->h);
	
	SDL_ConvertPixels(surface->w, surface->h, surface->format->format, surface->pixels, surface->pitch, SDL_PIXELFORMAT_ARGB8888, &texture->pixels[0], surface->w * 4);
	
	*ppTexture = texture.release();
	
	return D3D_OK;
}
