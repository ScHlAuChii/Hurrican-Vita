#include <d3d9.h>

#include <memory>

typedef std::shared_ptr<uint8_t> Pixels;

class Texture : public IDirect3DTexture9
{
public:
	
	int width = 0;
	int height = 0;
	Pixels pixels;
	
	virtual ~Texture();
	
	HRESULT GetLevelDesc(UINT Level, D3DSURFACE_DESC *pDesc) override;
	HRESULT LockRect(UINT Level, D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags) override;
	HRESULT UnlockRect(UINT Level) override;
};

void check();
