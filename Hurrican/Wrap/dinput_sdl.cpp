#include "dinput.h"

#include "SDL_keyboard.h"

struct KeyBinding
{
	Keyboard_Device dinput;
	SDL_Scancode sdl;
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
	{ DIK_SPACE, SDL_SCANCODE_SPACE }
};

static const size_t key_binding_count = sizeof(key_bindings) / sizeof(key_bindings[0]);

HRESULT DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter)
{
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
	memset(lpvData, 0, cbData);
	
	const Uint8 *const src = SDL_GetKeyboardState(nullptr);
	uint8_t *const dst = static_cast<uint8_t *>(lpvData);
	
	for (size_t i = 0; i < key_binding_count; ++i)
	{
		const KeyBinding &binding = key_bindings[i];
		if (src[binding.sdl])
		{
			dst[binding.dinput] = 0x80;
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

