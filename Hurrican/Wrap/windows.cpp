#include "windows.h"

#include <time.h>

const BOOL FALSE = 0;
const LPCTSTR IDC_ARROW = MAKEINTRESOURCE(32512);
const int INFINITE = -1;
const BOOL TRUE = 1;

HDC BeginPaint(HWND hwnd, LPPAINTSTRUCT lpPaint)
{
	memset(lpPaint, 0, sizeof(*lpPaint));
	
	return nullptr;
}

BOOL BitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int   nYSrc, DWORD dwRop)
{
	return TRUE;
}

HDC CreateCompatibleDC(HDC hdc)
{
	return nullptr;
}

HBRUSH CreateSolidBrush(COLORREF)
{
	return nullptr;
}

HWND CreateWindow(LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	return nullptr;
}

LRESULT DefWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

BOOL DeleteDC(HDC hdc)
{
	return TRUE;
}

BOOL DeleteFile(LPCTSTR lpFileName)
{
	return TRUE;
}

BOOL DeleteObject(HGDIOBJ hObject)
{
	return TRUE;
}

LRESULT DispatchMessage(const MSG *lpmsg)
{
	return 0;
}

BOOL EndPaint(HWND hWnd, const PAINTSTRUCT *lpPaint)
{
	return TRUE;
}

BYTE GetBValue(DWORD rgb)
{
	return 0;
}

HWND GetDesktopWindow()
{
	return nullptr;
}

BYTE GetGValue(DWORD rgb)
{
	return 0;
}

HMODULE GetModuleHandle(LPCTSTR lpModuleName)
{
	return nullptr;
}

int GetObject(HGDIOBJ hgdiobj, int cbBuffer,LPVOID lpvObject)
{
	memset(lpvObject, 0, cbBuffer);
	
	return cbBuffer;
}

COLORREF GetPixel(HDC hdc, int nXPos, int nYPos)
{
	return 0;
}

BYTE GetRValue(DWORD rgb)
{
	return 0;
}

DWORD GetTickCount()
{
	return clock() / (CLOCKS_PER_SEC / 1000);
}

BOOL InvalidateRect(HWND hWnd, const RECT *lpRect, BOOL bErase)
{
	return TRUE;
}

HBITMAP LoadBitmap(HINSTANCE hInstance, LPCTSTR lpBitmapName)
{
	return nullptr;
}

HCURSOR LoadCursor(HINSTANCE hInstance, LPCTSTR lpCursorName)
{
	return nullptr;
}

HICON LoadIcon(HINSTANCE hInstance, LPCTSTR lpIconName)
{
	return nullptr;
}

HANDLE LoadImage(HINSTANCE hinst, LPCTSTR lpszName, UINT uType, int cxDesired, int cyDesired, UINT fuLoad)
{
	return nullptr;
}

WORD LOWORD(DWORD dwValue)
{
	return dwValue;
}

LPTSTR MAKEINTRESOURCE(WORD wInteger)
{
	return reinterpret_cast<LPTSTR>(wInteger);
}

int MessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)
{
	fputs(lpText, stderr);
	return 0;
}

void PostQuitMessage(int nExitCode)
{
}

BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount)
{
	lpPerformanceCount->QuadPart = clock();
	return TRUE;
}

BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency)
{
	lpFrequency->QuadPart = CLOCKS_PER_SEC;
	return TRUE;
}

ATOM RegisterClassEx(const WNDCLASSEX *lpwcx)
{
	return 1;
}

COLORREF RGB(BYTE byRed, BYTE byGreen, BYTE byBlue)
{
	return 0;
}

HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj)
{
	return nullptr;
}

LRESULT SendMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

int ShowCursor(BOOL bShow)
{
	return 1;
}

BOOL ShowWindow(HWND hWnd, int nCmdShow)
{
	return TRUE;
}

void Sleep(DWORD dwMilliseconds)
{
}

BOOL SUCCEEDED(HRESULT hr)
{
	return hr == 0;
}

DWORD timeGetTime()
{
	return GetTickCount();
}

BOOL TranslateMessage(const MSG *lpMsg)
{
	return TRUE;
}

BOOL UpdateWindow(HWND hWnd)
{
	return TRUE;
}

void ZeroMemory(void *Destination, size_t Length)
{
	memset(Destination, 0, Length);
}
