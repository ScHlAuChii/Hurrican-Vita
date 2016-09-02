#include "d3dx9.h"

#include "d3d9_sdl.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <algorithm>
#include <assert.h>
#include <memory>

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
	
	int w = 0;
	int h = 0;
	const Pixels pixels(stbi_load(pSrcFile, &w, &h, nullptr, 4), &stbi_image_free);
	assert(pixels);
	
	TexturePtr texture(new Texture);
	texture->width = w;
	texture->height = h;
	texture->pixels = pixels;
	
	const uint8_t *const pixels_end = pixels.get() + (w * h * 4);
	for (uint8_t *pixel = pixels.get(); pixel != pixels_end; pixel += 4)
	{
		if ((pixel[0] == 0xff) && (pixel[1] == 0x00) && (pixel[2] == 0xff) && (pixel[3] == 0xff))
		{
			pixel[0] = 0x00;
			pixel[2] = 0x00;
			pixel[3] = 0x00;
		}
	}
	
	glGenTextures(1, &texture->texture);
	check();
	
	glBindTexture(GL_TEXTURE_2D, texture->texture);
	check();
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels.get());
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
