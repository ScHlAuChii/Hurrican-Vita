#include "d3d9.h"

#include <vector>

typedef std::vector<D3DCOLOR> Pixels;

class Texture : public IDirect3DTexture9
{
public:
	
	size_t width = 0;
	size_t height = 0;
	Pixels pixels;
	
	HRESULT GetLevelDesc(UINT Level, D3DSURFACE_DESC *pDesc) override;
	HRESULT LockRect(UINT Level, D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags) override;
	HRESULT UnlockRect(UINT Level) override;
};
