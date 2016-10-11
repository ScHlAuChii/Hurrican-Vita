#include "d3dx9.h"

#include "d3d9_vita.h"

#include "vita2d/libvita2d/include/vita2d.h"

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
	
	VitaTexturePtr vt(vita2d_load_BMP_file(pSrcFile), &vita2d_free_texture);
	if (!vt)
	{
		vt = VitaTexturePtr(vita2d_load_PNG_file(pSrcFile), &vita2d_free_texture);
		if (!vt)
		{
			return D3DERR_DEVICENOTRESET;
		}
	}
	
	TexturePtr texture(new Texture);
	texture->texture = vt;
	
	uint8_t *const pixels_start = static_cast<uint8_t *>(vita2d_texture_get_datap(vt.get()));
	const uint8_t *const pixels_end = pixels_start + (vita2d_texture_get_height(vt.get()) * vita2d_texture_get_stride(vt.get()));
	for (uint8_t *pixel = pixels_start; pixel < pixels_end; pixel += 4)
	{
		if ((pixel[0] == 0xff) && (pixel[1] == 0x00) && (pixel[2] == 0xff) && (pixel[3] == 0xff))
		{
			pixel[0] = 0x00;
			pixel[2] = 0x00;
			pixel[3] = 0x00;
		}
	}
	
	*ppTexture = texture.release();
	
	return D3D_OK;
}
