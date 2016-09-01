#include "d3dx9.h"

const float D3DX_PI = M_PI;

HRESULT D3DXCreateTextureFromFileInMemoryEx(LPDIRECT3DDEVICE9 pDevice, LPCVOID pSrcData, UINT SrcDataSize, UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter, DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, LPDIRECT3DTEXTURE9 *ppTexture)
{
	*ppTexture = nullptr;
	
	return D3D_OK;
}

HRESULT D3DXLoadSurfaceFromFile(LPDIRECT3DSURFACE9 pDestSurface, const PALETTEENTRY *pDestPalette, const RECT *pDestRect, LPCTSTR pSrcFile, const RECT *pSrcRect, DWORD Filter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo)
{
	return D3D_OK;
}

D3DXMATRIX *D3DXMatrixIdentity(D3DXMATRIX *pOut)
{
	memset(pOut, 0, sizeof(*pOut));
	
	return pOut;
}

D3DXMATRIX* D3DXMatrixMultiply(D3DXMATRIX *pOut, const D3DXMATRIX *pM1, const D3DXMATRIX *pM2)
{
	memset(pOut, 0, sizeof(*pOut));
	
	return pOut;
}

D3DXMATRIX *D3DXMatrixOrthoOffCenterLH(D3DXMATRIX *pOut, FLOAT l, FLOAT r, FLOAT b, FLOAT t, FLOAT zn, FLOAT zf)
{
	memset(pOut, 0, sizeof(*pOut));
	pOut->_11 = 2 / (r - l);
	pOut->_22 = 2 / (t - b);
	pOut->_33 = 1 / (zf - zn);
	pOut->_41 = (l + r) / (l - r);
	pOut->_42 = (t + b) / (b - t);
	pOut->_43 = zn / (zn - zf);
	pOut->_44 = 1;
	
	return pOut;
}

D3DXMATRIX* D3DXMatrixRotationZ(D3DXMATRIX *pOut, FLOAT Angle)
{
	memset(pOut, 0, sizeof(*pOut));
	
	return pOut;
}

D3DXMATRIX* D3DXMatrixTranslation(D3DXMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z)
{
	memset(pOut, 0, sizeof(*pOut));
	
	return pOut;
}
