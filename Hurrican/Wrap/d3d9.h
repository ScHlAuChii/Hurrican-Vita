#pragma once

#include "com.h"

typedef uint32_t D3DCOLOR;

enum D3D
{
	D3D_OK,
	D3DERR_DEVICELOST,
	D3DERR_DEVICENOTRESET,
};

enum D3DADAPTER
{
	D3DADAPTER_DEFAULT,
};

enum D3DBLEND
{
	D3DBLEND_DESTALPHA,
	D3DBLEND_SRCALPHA,
	D3DBLEND_INVSRCALPHA,
};

enum D3DCULL
{
	D3DCULL_NONE,
};

enum D3DDEVTYPE
{
	D3DDEVTYPE_HAL,
	D3DDEVTYPE_REF,
};

struct D3DPSHADERCAPS2_0
{
	DWORD Caps;
	INT DynamicFlowControlDepth;
	INT NumTemps;
	INT StaticFlowControlDepth;
	INT NumInstructionSlots;
};

struct D3DVSHADERCAPS2_0
{
	DWORD Caps;
	INT DynamicFlowControlDepth;
	INT NumTemps;
	INT StaticFlowControlDepth;
};

struct D3DCAPS9
{
	D3DDEVTYPE DeviceType;
	UINT AdapterOrdinal;
	DWORD Caps;
	DWORD Caps2;
	DWORD Caps3;
	DWORD PresentationIntervals;
	DWORD CursorCaps;
	DWORD DevCaps;
	DWORD PrimitiveMiscCaps;
	DWORD RasterCaps;
	DWORD ZCmpCaps;
	DWORD SrcBlendCaps;
	DWORD DestBlendCaps;
	DWORD AlphaCmpCaps;
	DWORD ShadeCaps;
	DWORD TextureCaps;
	DWORD TextureFilterCaps;
	DWORD CubeTextureFilterCaps;
	DWORD VolumeTextureFilterCaps;
	DWORD TextureAddressCaps;
	DWORD VolumeTextureAddressCaps;
	DWORD LineCaps;
	DWORD MaxTextureWidth;
	DWORD MaxTextureHeight;
	DWORD MaxVolumeExtent;
	DWORD MaxTextureRepeat;
	DWORD MaxTextureAspectRatio;
	DWORD MaxAnisotropy;
	float MaxVertexW;
	float GuardBandLeft;
	float GuardBandTop;
	float GuardBandRight;
	float GuardBandBottom;
	float ExtentsAdjust;
	DWORD StencilCaps;
	DWORD FVFCaps;
	DWORD TextureOpCaps;
	DWORD MaxTextureBlendStages;
	DWORD MaxSimultaneousTextures;
	DWORD VertexProcessingCaps;
	DWORD MaxActiveLights;
	DWORD MaxUserClipPlanes;
	DWORD MaxVertexBlendMatrices;
	DWORD MaxVertexBlendMatrixIndex;
	float MaxPointSize;
	DWORD MaxPrimitiveCount;
	DWORD MaxVertexIndex;
	DWORD MaxStreams;
	DWORD MaxStreamStride;
	DWORD VertexShaderVersion;
	DWORD MaxVertexShaderConst;
	DWORD PixelShaderVersion;
	float PixelShader1xMaxValue;
	DWORD DevCaps2;
	UINT MasterAdapterOrdinal;
	UINT AdapterOrdinalInGroup;
	UINT NumberOfAdaptersInGroup;
	DWORD DeclTypes;
	DWORD NumSimultaneousRTs;
	DWORD StretchRectFilterCaps;
	D3DVSHADERCAPS2_0 VS20Caps;
	D3DPSHADERCAPS2_0 PS20Caps;
	DWORD VertexTextureFilterCaps;
	DWORD MaxVShaderInstructionsExecuted;
	DWORD MaxPShaderInstructionsExecuted;
	DWORD MaxVertexShader30InstructionSlots;
	DWORD MaxPixelShader30InstructionSlots;
	DWORD Reserved2;
	DWORD Reserved3;
};

enum D3DCLEAR
{
	D3DCLEAR_TARGET = 1,
	D3DCLEAR_ZBUFFER = 2,
};

enum D3DCREATE
{
	D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	D3DCREATE_HARDWARE_VERTEXPROCESSING,
};

struct D3DDISPLAYMODE
{
};

enum D3DFORMAT
{
	D3DFMT_UNKNOWN,
	D3DFMT_D16,
	D3DFMT_R5G6B5,
	D3DFMT_X8R8G8B8,
};

enum D3DFVF
{
	D3DFVF_DIFFUSE,
	D3DFVF_TEX1,
	D3DFVF_XYZ,
};

struct D3DLOCKED_RECT
{
	INT Pitch;
	void *pBits;
};

struct D3DMATRIX
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

enum D3DMULTISAMPLE_TYPE
{
};

enum D3DPOOL
{
	D3DPOOL_DEFAULT,
	D3DPOOL_MANAGED,
};

enum D3DSWAPEFFECT
{
	D3DSWAPEFFECT_DISCARD,
};

enum
{
	D3DPRESENT_INTERVAL_IMMEDIATE = 0,
	D3DPRESENT_INTERVAL_ONE = 1,
	D3DPRESENT_RATE_DEFAULT = 0,
};

struct D3DPRESENT_PARAMETERS
{
	UINT BackBufferWidth;
	UINT BackBufferHeight;
	D3DFORMAT BackBufferFormat;
	UINT BackBufferCount;
	D3DMULTISAMPLE_TYPE MultiSampleType;
	DWORD MultiSampleQuality;
	D3DSWAPEFFECT SwapEffect;
	HWND hDeviceWindow;
	BOOL Windowed;
	BOOL EnableAutoDepthStencil;
	D3DFORMAT AutoDepthStencilFormat;
	DWORD Flags;
	UINT FullScreen_RefreshRateInHz;
	UINT PresentationInterval;
};

enum D3DPRESENTFLAG
{
	D3DPRESENTFLAG_LOCKABLE_BACKBUFFER,
};

enum D3DPRIMITIVETYPE
{
	D3DPT_LINELIST,
	D3DPT_TRIANGLELIST,
	D3DPT_TRIANGLESTRIP,
};

enum D3DRENDERSTATETYPE
{
	D3DRS_ALPHABLENDENABLE,
	D3DRS_AMBIENT,
	D3DRS_CULLMODE,
	D3DRS_DESTBLEND,
	D3DRS_LIGHTING,
	D3DRS_SRCBLEND,
	D3DRS_ZENABLE,
};

enum D3DRESOURCETYPE
{
};

enum D3DSAMPLERSTATETYPE
{
	D3DSAMP_MAGFILTER,
	D3DSAMP_MINFILTER,
};

struct D3DSURFACE_DESC
{
	D3DFORMAT Format;
	D3DRESOURCETYPE Type;
	DWORD Usage;
	D3DPOOL Pool;
	D3DMULTISAMPLE_TYPE MultiSampleType;
	DWORD MultiSampleQuality;
	UINT Width;
	UINT Height;
};

enum D3DTEXF
{
	D3DTEXF_LINEAR,
	D3DTEXF_POINT,
};

enum D3DPTEXTURECAPS
{
	D3DPTEXTURECAPS_POW2,
	D3DPTEXTURECAPS_SQUAREONLY,
};

enum D3DTEXTUREFILTERTYPE
{
	D3DTEXF_NONE,
};

enum D3DTEXTURESTAGESTATETYPE
{
	D3DTSS_ALPHAOP,
};

enum D3DTOP
{
	D3DTOP_MODULATE,
};

enum D3DTRANSFORMSTATETYPE
{
	D3DTS_PROJECTION,
	D3DTS_VIEW,
	D3DTS_WORLD,
};

enum D3DZB
{
	D3DZB_FALSE,
};

class IDirect3DSurface9 : public IUnknown
{
};

typedef IDirect3DSurface9 *LPDIRECT3DSURFACE9;

class IDirect3DBaseTexture9 : public IUnknown
{
};

class IDirect3DTexture9 : public IDirect3DBaseTexture9
{
public:
	
	virtual HRESULT GetLevelDesc(UINT Level, D3DSURFACE_DESC *pDesc) = 0;
	virtual HRESULT LockRect(UINT Level, D3DLOCKED_RECT *pLockedRect, const RECT *pRect, DWORD Flags) = 0;
	virtual HRESULT UnlockRect(UINT Level) = 0;
};

typedef IDirect3DTexture9 *LPDIRECT3DTEXTURE9;

class IDirect3DDevice9 : public IUnknown
{
public:
	
	virtual HRESULT BeginScene() = 0;
	virtual HRESULT Clear(int a, const void *b, int buffers, D3DCOLOR color, float z, int c) = 0;
	virtual HRESULT CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle) = 0;
	virtual HRESULT DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void             *pVertexStreamZeroData, UINT VertexStreamZeroStride) = 0;
	virtual HRESULT EndScene() = 0;
	virtual HRESULT GetDeviceCaps(D3DCAPS9 *pCaps) = 0;
	virtual HRESULT Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion) = 0;
	virtual HRESULT Reset(D3DPRESENT_PARAMETERS *pPresentationParameters) = 0;
	virtual HRESULT SetFVF(DWORD FVF) = 0;
	virtual HRESULT SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) = 0;
	virtual HRESULT SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) = 0;
	virtual HRESULT SetTexture(DWORD Sampler, IDirect3DBaseTexture9 *pTexture) = 0;
	virtual HRESULT SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) = 0;
	virtual HRESULT SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix) = 0;
	virtual HRESULT StretchRect(IDirect3DSurface9 *pSourceSurface, const RECT *pSourceRect, IDirect3DSurface9 *pDestSurface, const RECT *pDestRect, D3DTEXTUREFILTERTYPE Filter) = 0;
	virtual HRESULT TestCooperativeLevel() = 0;
};

typedef IDirect3DDevice9 *LPDIRECT3DDEVICE9;

class IDirect3D9 : public IUnknown
{
public:
	
	virtual HRESULT CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface) = 0;
};

typedef IDirect3D9 *LPDIRECT3D9;
typedef void *LPDIRECT3DVERTEXBUFFER9;

extern const UINT D3D_SDK_VERSION	;

D3DCOLOR D3DCOLOR_RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
D3DCOLOR D3DCOLOR_XRGB(uint8_t r, uint8_t g, uint8_t b);
IDirect3D9 *Direct3DCreate9(UINT SDKVersion);
