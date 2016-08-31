#include "d3d9.h"

const UINT D3D_SDK_VERSION = 0x0900;

D3DCOLOR D3DCOLOR_RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return 0;
}

D3DCOLOR D3DCOLOR_XRGB(uint8_t r, uint8_t g, uint8_t b)
{
	return D3DCOLOR_RGBA(r, g, b, 255);
}
