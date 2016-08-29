#include "dinput.h"

const DIDATAFORMAT c_dfDIJoystick2 = {};
const DIDATAFORMAT c_dfDIKeyboard = {};
const GUID GUID_ConstantForce = {};
const GUID GUID_RampForce = {};
const GUID GUID_SysKeyboard = {};
const GUID DIPROP_KEYNAME = {};
const GUID DIPROP_RANGE = {};
const IID IID_IDirectInput8 = {};

HRESULT DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter)
{
	return DI_OK;
}
