#include "dinput.h"

#include <psp2/ctrl.h>

struct KeyBinding
{
	Keyboard_Device key;
	unsigned int button;
};

class DirectInput : public IDirectInput8
{
public:
	
	HRESULT CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8 *lplpDirectInputDevice, LPUNKNOWN pUnkOuter) override;
	HRESULT EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags) override;
};

class Keyboard : public IDirectInputDevice8
{
public:
	
	HRESULT Acquire() override;
	HRESULT CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT *ppdeff, LPUNKNOWN punkOuter) override;
	HRESULT GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) override;
	HRESULT GetDeviceState(DWORD cbData, LPVOID lpvData) override;
	HRESULT GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph) override;
	HRESULT Poll() override;
	HRESULT SetCooperativeLevel(HWND hwnd, DWORD dwFlags) override;
	HRESULT SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph) override;
	HRESULT SetDataFormat(LPCDIDATAFORMAT lpdf) override;
	HRESULT Unacquire() override;
};

static const KeyBinding key_bindings[] =
{
	{ DIK_DOWN, SCE_CTRL_DOWN },
	{ DIK_END, SCE_CTRL_SELECT },
	{ DIK_ESCAPE, SCE_CTRL_START },
	{ DIK_LALT, SCE_CTRL_CROSS },
	{ DIK_LCONTROL, SCE_CTRL_TRIANGLE },
	{ DIK_LEFT, SCE_CTRL_LEFT },
	{ DIK_LSHIFT, SCE_CTRL_TRIANGLE },
	{ DIK_RCONTROL, SCE_CTRL_SQUARE },
	{ DIK_RETURN, SCE_CTRL_START },
	{ DIK_RIGHT, SCE_CTRL_RIGHT },
	{ DIK_RSHIFT, SCE_CTRL_LTRIGGER },
	{ DIK_SPACE, SCE_CTRL_RTRIGGER },
	{ DIK_UP, SCE_CTRL_UP },
};

static const size_t key_binding_count = sizeof(key_bindings) / sizeof(key_bindings[0]);

HRESULT DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter)
{
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
	
	*ppvOut = new DirectInput();
	
	return DI_OK;
}

HRESULT DirectInput::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8 *lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	if (&rguid == &GUID_SysKeyboard)
	{
		*lplpDirectInputDevice = new Keyboard();
		return DI_OK;
	}
	else
	{
		*lplpDirectInputDevice = nullptr;
		return DIERR_DEVICENOTREG;
	}
}

HRESULT DirectInput::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return DI_OK;
}

HRESULT Keyboard::Acquire()
{
	return DI_OK;
}

HRESULT Keyboard::CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT *ppdeff, LPUNKNOWN punkOuter)
{
	*ppdeff = nullptr;
	
	return DI_OK;
}

HRESULT Keyboard::GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{
	memset(rgdod, 0, cbObjectData);
	
	return DI_OK;
}

HRESULT Keyboard::GetDeviceState(DWORD cbData, LPVOID lpvData)
{
	uint8_t *const keys = static_cast<uint8_t *>(lpvData);
	
	memset(lpvData, 0, cbData);
	
	SceCtrlData pad = {};
	sceCtrlPeekBufferPositive(0, &pad, 1);
	
	for (size_t i = 0; i < key_binding_count; ++i)
	{
		const KeyBinding &binding = key_bindings[i];
		if (pad.buttons & binding.button)
		{
			keys[binding.key] = 0x80;
		}
	}
	
	return DI_OK;
}

HRESULT Keyboard::GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph)
{
	memset(pdiph, 0, sizeof(*pdiph));
	
	return DI_OK;
}

HRESULT Keyboard::Poll()
{
	return DI_OK;
}

HRESULT Keyboard::SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
{
	return DI_OK;
}

HRESULT Keyboard::SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph)
{
	return DI_OK;
}

HRESULT Keyboard::SetDataFormat(LPCDIDATAFORMAT lpdf)
{
	return DI_OK;
}

HRESULT Keyboard::Unacquire()
{
	return DI_OK;
}

