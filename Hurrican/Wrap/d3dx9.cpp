#include "d3dx9.h"

const float D3DX_PI = 3.14159265358979323846264338327950288f;

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
	pOut->_11 = 1;
	pOut->_22 = 1;
	pOut->_33 = 1;
	pOut->_44 = 1;
	
	return pOut;
}

D3DXMATRIX* D3DXMatrixMultiply(D3DXMATRIX *pOut, const D3DXMATRIX *pM1, const D3DXMATRIX *pM2)
{
	D3DXMATRIX result;
	
	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			result.m[row][column] =
			pM1->m[row][0] * pM2->m[0][column] +
			pM1->m[row][1] * pM2->m[1][column] +
			pM1->m[row][2] * pM2->m[2][column] +
			pM1->m[row][3] * pM2->m[3][column];
		}
	}
	
	*pOut = result;
	
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
	pOut->_11 = cosf(Angle);
	pOut->_12 = sinf(Angle);
	pOut->_21 = -sinf(Angle);
	pOut->_22 = cosf(Angle);
	pOut->_33 = 1;
	pOut->_44 = 1;
	
	return pOut;
}

D3DXMATRIX* D3DXMatrixTranslation(D3DXMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z)
{
	memset(pOut, 0, sizeof(*pOut));
	pOut->_11 = 1;
	pOut->_22 = 1;
	pOut->_33 = 1;
	pOut->_41 = x;
	pOut->_42 = y;
	pOut->_43 = z;
	pOut->_44 = 1;
	
	return pOut;
}
