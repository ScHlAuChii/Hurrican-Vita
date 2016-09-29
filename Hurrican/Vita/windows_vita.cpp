#include "windows.h"

#include <psp2/rtc.h>

#include <assert.h>

static WNDCLASSEX wndclass;

HWND CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	return &wndclass;
}

LRESULT DispatchMessage(const MSG *lpmsg)
{
	return wndclass.lpfnWndProc(lpmsg->hwnd, lpmsg->message, lpmsg->wParam, lpmsg->lParam);
}

DWORD GetTickCount()
{
	return 0;
}

BOOL GetWindowRect(HWND hWnd, LPRECT lpRect)
{
	assert(hWnd == nullptr);
	
	lpRect->left = 0;
	lpRect->top = 0;
	lpRect->right = 960;
	lpRect->bottom = 544;
	
	return TRUE;
}

BOOL PeekMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT  wRemoveMsg)
{
	memset(lpMsg, 0, sizeof(*lpMsg));
	
	return FALSE;
}

BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount)
{
	SceRtcTick tick = {};
	sceRtcGetCurrentTick(&tick);
	
	lpPerformanceCount->QuadPart = tick.tick;
	
	return TRUE;
}

BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency)
{
	lpFrequency->QuadPart = sceRtcGetTickResolution();
	
	return TRUE;
}

ATOM RegisterClassEx(const WNDCLASSEX *lpwcx)
{
	wndclass = *lpwcx;
	
	return 1;
}
