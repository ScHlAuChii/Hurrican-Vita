#include "d3dx9.h"

#include "d3d9_vita.h"

#include "vita2d/libvita2d/include/vita2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <assert.h>

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
	typedef std::unique_ptr<uint8_t, void (*)(void *)> Pixels;
	const Pixels pixels(stbi_load(pSrcFile, &w, &h, nullptr, 4), &stbi_image_free);
	
	const VitaTexturePtr vt(vita2d_create_empty_texture(w, h), &vita2d_free_texture);
	const int stride = vita2d_texture_get_stride(vt.get());
	
	const uint8_t *src = pixels.get();
	uint8_t *const dst_start = static_cast<uint8_t *>(vita2d_texture_get_datap(vt.get()));
	for (int y = 0; y < h; ++y)
	{
		uint8_t *const dst_row_begin = dst_start + (y * stride);
		const uint8_t *const dst_row_end = dst_row_begin + (w * 4);
		for (uint8_t *dst = dst_row_begin; dst < dst_row_end; dst += 4)
		{
			const uint8_t r = *src++;
			const uint8_t g = *src++;
			const uint8_t b = *src++;
			const uint8_t a = *src++;
			
			if ((r == 0xff) && (g == 0x00) && (b == 0xff) && (a == 0xff))
			{
				dst[0] = 0;
				dst[1] = 0;
				dst[2] = 0;
				dst[3] = 0;
			}
			else
			{
				dst[0] = r;
				dst[1] = g;
				dst[2] = b;
				dst[3] = a;
			}
		}
	}
	
	TexturePtr texture(new Texture);
	texture->texture = vt;
	
	*ppTexture = texture.release();
	
	return D3D_OK;
}
