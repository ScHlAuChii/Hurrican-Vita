#include "d3dx9.h"

#include "d3d9_sdl.h"

#include "SDL_surface.h"

#include <algorithm>
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
	
	const SurfacePtr file_surface(SDL_LoadBMP(pSrcFile), &SDL_FreeSurface);
	assert(file_surface);
	
	TexturePtr texture(new Texture);
	texture->width = file_surface->w;
	texture->height = file_surface->h;
	texture->pixels.resize(file_surface->w * file_surface->h);
	
	const SurfacePtr texture_surface(SDL_CreateRGBSurfaceFrom(texture->pixels.data(), texture->width, texture->height, 32, texture->width * 4, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000), &SDL_FreeSurface);
	assert(texture_surface);
	
	SDL_BlitSurface(file_surface.get(), nullptr, texture_surface.get(), nullptr);
	
	std::replace(texture->pixels.begin(), texture->pixels.end(), 0xffff00ff, uint32_t(0));
	
	glGenTextures(1, &texture->texture);
	check();
	
	glBindTexture(GL_TEXTURE_2D, texture->texture);
	check();
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels.data());
	check();
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	check();
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	check();
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	check();
	
	*ppTexture = texture.release();
	
	return D3D_OK;
}
