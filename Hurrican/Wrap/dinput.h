#pragma once

#include "com.h"

enum
{
	DI_DEGREES = 1,
	DI_FFNOMINALMAX = 1,
	DI_SECONDS = 1000,
};

enum DI : HRESULT
{
	DI_OK,
	DIERR_DEVICENOTREG,
	DIERR_INPUTLOST,
};

enum DI8DEVCLASS
{
	DI8DEVCLASS_GAMECTRL,
};

struct DICONSTANTFORCE
{
	LONG lMagnitude;
};

struct DIDATAFORMAT
{
};

typedef const DIDATAFORMAT *LPCDIDATAFORMAT;

struct DIDEVICEINSTANCE
{
	GUID guidInstance;
	const char *tszProductName = nullptr;
};

typedef const DIDEVICEINSTANCE *LPCDIDEVICEINSTANCE;
typedef DIDEVICEINSTANCE *LPDIDEVICEINSTANCE;

struct DIDEVICEOBJECTDATA
{
	DWORD dwOfs;
	DWORD dwData;
	DWORD dwTimeStamp;
	DWORD dwSequence;
	UINT_PTR uAppData;
};

typedef DIDEVICEOBJECTDATA *LPDIDEVICEOBJECTDATA;

enum DIEB
{
	DIEB_NOTRIGGER,
};

enum DIENUM
{
	DIENUM_CONTINUE,
	DIENUM_STOP,
};

struct DIENVELOPE
{
	DWORD dwSize;
	DWORD dwAttackLevel;
	DWORD dwAttackTime;
	DWORD dwFadeLevel;
	DWORD dwFadeTime;
};

typedef DIENVELOPE *LPDIENVELOPE;

enum DIEFF
{
	DIEFF_OBJECTOFFSETS = 1,
	DIEFF_CARTESIAN = 2,
	DIEFF_POLAR = 4,
};

struct DIEFFECT
{
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwDuration;
	DWORD dwSamplePeriod;
	DWORD dwGain;
	DWORD dwTriggerButton;
	DWORD dwTriggerRepeatInterval;
	DWORD cAxes;
	LPDWORD rgdwAxes;
	LPLONG rglDirection;
	LPDIENVELOPE lpEnvelope;
	DWORD cbTypeSpecificParams;
	LPVOID lpvTypeSpecificParams;
	DWORD dwStartDelay;
};

typedef const DIEFFECT *LPCDIEFFECT;

enum DIJOFS
{
	DIJOFS_X,
	DIJOFS_Y,
};

struct DIJOYSTATE2
{
	LONG lX;
	LONG lY;
	LONG lZ;
	LONG lRx;
	LONG lRy;
	LONG lRz;
	LONG rglSlider[2];
	DWORD rgdwPOV[4];
	BYTE rgbButtons[128];
	LONG lVX;
	LONG lVY;
	LONG lVZ;
	LONG lVRx;
	LONG lVRy;
	LONG lVRz;
	LONG rglVSlider[2];
	LONG lAX;
	LONG lAY;
	LONG lAZ;
	LONG lARx;
	LONG lARy;
	LONG lARz;
	LONG rglASlider[2];
	LONG lFX;
	LONG lFY;
	LONG lFZ;
	LONG lFRx;
	LONG lFRy;
	LONG lFRz;
	LONG rglFSlider[2];
};

enum DIMOFS
{
	DIMOFS_X,
	DIMOFS_Y,
	DIMOFS_BUTTON0,
	DIMOFS_BUTTON1,
	DIMOFS_BUTTON2,
};

struct DIMOUSESTATE
{
	LONG lX;
	LONG lY;
	LONG lZ;
	BYTE rgbButtons[4];
};

enum DIPH
{
	DIPH_BYOFFSET,
};

struct DIPROPHEADER
{
	DWORD dwSize;
	DWORD dwHeaderSize;
	DWORD dwObj;
	DWORD dwHow;
};

typedef const DIPROPHEADER *LPCDIPROPHEADER;
typedef DIPROPHEADER *LPDIPROPHEADER;

struct DIPROPRANGE
{
	DIPROPHEADER diph;
	LONG lMin;
	LONG lMax;
};

struct DIPROPSTRING
{
	DIPROPHEADER diph;
	WCHAR wsz[MAX_PATH];
};

struct DIRAMPFORCE
{
	LONG lStart;
	LONG lEnd;
};

enum DISCL
{
	DISCL_NONEXCLUSIVE = 0,
	DISCL_BACKGROUND = 0,
	DISCL_EXCLUSIVE = 1,
	DISCL_FOREGROUND = 2,
};

enum Keyboard_Device
{
	DIK_0,
	DIK_1,
	DIK_2,
	DIK_3,
	DIK_4,
	DIK_5,
	DIK_6,
	DIK_7,
	DIK_8,
	DIK_9,
	DIK_A,
	DIK_ABNT_C1,
	DIK_ABNT_C2,
	DIK_ADD,
	DIK_APOSTROPHE,
	DIK_APPS,
	DIK_AT,
	DIK_AX,
	DIK_B,
	DIK_BACK,
	DIK_BACKSLASH,
	DIK_C,
	DIK_CALCULATOR,
	DIK_CAPITAL,
	DIK_COLON,
	DIK_COMMA,
	DIK_CONVERT,
	DIK_D,
	DIK_DECIMAL,
	DIK_DELETE,
	DIK_DIVIDE,
	DIK_DOWN,
	DIK_E,
	DIK_END,
	DIK_EQUALS,
	DIK_ESCAPE,
	DIK_F,
	DIK_F1,
	DIK_F2,
	DIK_F3,
	DIK_F4,
	DIK_F5,
	DIK_F6,
	DIK_F7,
	DIK_F8,
	DIK_F9,
	DIK_F10,
	DIK_F11,
	DIK_F12,
	DIK_F13,
	DIK_F14,
	DIK_F15,
	DIK_G,
	DIK_GRAVE,
	DIK_H,
	DIK_HOME,
	DIK_I,
	DIK_INSERT,
	DIK_J,
	DIK_K,
	DIK_KANA,
	DIK_KANJI,
	DIK_L,
	DIK_LBRACKET,
	DIK_LCONTROL,
	DIK_LEFT,
	DIK_LMENU,
	DIK_LSHIFT,
	DIK_LWIN,
	DIK_M,
	DIK_MAIL,
	DIK_MEDIASELECT,
	DIK_MEDIASTOP,
	DIK_MINUS,
	DIK_MULTIPLY,
	DIK_MUTE,
	DIK_MYCOMPUTER,
	DIK_N,
	DIK_NEXT,
	DIK_NEXTTRACK,
	DIK_NOCONVERT,
	DIK_NUMLOCK,
	DIK_NUMPAD0,
	DIK_NUMPAD1,
	DIK_NUMPAD2,
	DIK_NUMPAD3,
	DIK_NUMPAD4,
	DIK_NUMPAD5,
	DIK_NUMPAD6,
	DIK_NUMPAD7,
	DIK_NUMPAD8,
	DIK_NUMPAD9,
	DIK_NUMPADCOMMA,
	DIK_NUMPADENTER,
	DIK_NUMPADEQUALS,
	DIK_O,
	DIK_OEM_102,
	DIK_P,
	DIK_PAUSE,
	DIK_PERIOD,
	DIK_PLAYPAUSE,
	DIK_POWER,
	DIK_PREVTRACK,
	DIK_PRIOR,
	DIK_Q,
	DIK_R,
	DIK_RBRACKET,
	DIK_RCONTROL,
	DIK_RETURN,
	DIK_RIGHT,
	DIK_RMENU,
	DIK_RSHIFT,
	DIK_RWIN,
	DIK_S,
	DIK_SCROLL,
	DIK_SEMICOLON,
	DIK_SLASH,
	DIK_SLEEP,
	DIK_SPACE,
	DIK_STOP,
	DIK_SUBTRACT,
	DIK_SYSRQ,
	DIK_T,
	DIK_TAB,
	DIK_U,
	DIK_UNDERLINE,
	DIK_UNLABELED,
	DIK_UP,
	DIK_V,
	DIK_VOLUMEDOWN,
	DIK_VOLUMEUP,
	DIK_W,
	DIK_WAKE,
	DIK_WEBBACK,
	DIK_WEBFAVORITES,
	DIK_WEBFORWARD,
	DIK_WEBHOME,
	DIK_WEBREFRESH,
	DIK_WEBSEARCH,
	DIK_WEBSTOP,
	DIK_X,
	DIK_Y,
	DIK_YEN,
	DIK_Z,
	
	DIK_BACKSPACE = DIK_BACK,
	DIK_LALT = DIK_LMENU,
};

class IDirectInputEffect : public IUnknown
{
public:
	
	virtual HRESULT Start(DWORD dwIterations, DWORD dwFlags) = 0;
	virtual HRESULT Stop() = 0;
};

typedef IDirectInputEffect *LPDIRECTINPUTEFFECT;

class IDirectInputDevice8 : public IUnknown
{
public:
	
	virtual HRESULT Acquire() = 0;
	virtual HRESULT CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT *ppdeff, LPUNKNOWN punkOuter) = 0;
	virtual HRESULT GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) = 0;
	virtual HRESULT GetDeviceState(DWORD cbData, LPVOID lpvData) = 0;
	virtual HRESULT GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph) = 0;
	virtual HRESULT Poll() = 0;
	virtual HRESULT SetCooperativeLevel(HWND hwnd, DWORD dwFlags) = 0;
	virtual HRESULT SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph) = 0;
	virtual HRESULT SetDataFormat(LPCDIDATAFORMAT lpdf) = 0;
	virtual HRESULT Unacquire() = 0;
};

typedef IDirectInputDevice8 *LPDIRECTINPUTDEVICE8;

typedef BOOL (*LPDIENUMDEVICESCALLBACK)(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);

class IDirectInput8 : public IUnknown
{
public:
	
	virtual HRESULT CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8 *lplpDirectInputDevice, LPUNKNOWN pUnkOuter) = 0;
	virtual HRESULT EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags) = 0;
};

typedef IDirectInput8 *LPDIRECTINPUT8;

extern const DIDATAFORMAT c_dfDIJoystick2;
extern const DIDATAFORMAT c_dfDIKeyboard;
extern const GUID GUID_ConstantForce;
extern const GUID GUID_RampForce;
extern const GUID GUID_SysKeyboard;
extern const GUID DIPROP_KEYNAME;
extern const GUID DIPROP_RANGE;
extern const IID IID_IDirectInput8;

HRESULT DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter);
