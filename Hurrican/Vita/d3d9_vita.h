#include <d3d9.h>

#include <memory>

struct vita2d_texture;

typedef std::shared_ptr<vita2d_texture> VitaTexturePtr;

class Texture : public IDirect3DTexture9
{
public:

	VitaTexturePtr texture;
	
	virtual ~Texture();
	
	HRESULT GetLevelDesc(UINT Level, D3DSURFACE_DESC *pDesc) override;
	HRESULT LockRect(UINT Level, D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags) override;
	HRESULT UnlockRect(UINT Level) override;
};
