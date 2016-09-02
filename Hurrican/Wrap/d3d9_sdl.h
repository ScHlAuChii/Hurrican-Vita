#include "d3d9.h"

#include "SDL_opengl.h"

#include <vector>

typedef std::shared_ptr<uint8_t> Pixels;

class Texture : public IDirect3DTexture9
{
public:
	
	GLsizei width = 0;
	GLsizei height = 0;
	GLuint texture = 0;
	Pixels pixels;
	
	virtual ~Texture();
	
	HRESULT GetLevelDesc(UINT Level, D3DSURFACE_DESC *pDesc) override;
	HRESULT LockRect(UINT Level, D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags) override;
	HRESULT UnlockRect(UINT Level) override;
};

void check();
