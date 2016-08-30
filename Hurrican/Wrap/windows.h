#pragma once

#include "safe.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CALLBACK
#define CONST const
#define WINAPI

typedef int ATOM;

typedef int32_t LONG;
typedef void *LPVOID;
typedef uint16_t WORD;

struct BITMAP
{
	LONG bmType;
	LONG bmWidth;
	LONG bmHeight;
	LONG bmWidthBytes;
	WORD bmPlanes;
	WORD bmBitsPixel;
	LPVOID bmBits;
};

typedef int BOOL;
typedef uint8_t BYTE;

enum CB
{
	CB_DIR,
	CB_ERR,
	CB_GETCOUNT,
	CB_GETLBTEXT,
};

typedef uint32_t COLORREF;

enum CS
{
	CS_HREDRAW = 1,
	CS_VREDRAW = 2,
};

enum DDL
{
	DDL_READWRITE,
};

typedef uint32_t DWORD;
typedef float FLOAT;

struct GUID
{
};

typedef void *HANDLE;
typedef void *HBITMAP;
typedef void *HBRUSH;
typedef void *HCURSOR;
typedef void *HDC;
typedef void *HGDIOBJ;
typedef void *HICON;
typedef void *HINSTANCE;
typedef void *HMENU;
typedef void *HMODULE;
typedef uint32_t HRESULT;
typedef void *HWND;

enum IMAGE
{
	IMAGE_BITMAP,
};

typedef int32_t INT;

typedef int64_t LONGLONG;

union LARGE_INTEGER
{
	struct
	{
		DWORD LowPart;
		LONG  HighPart;
	};
	struct
	{
		DWORD LowPart;
		LONG  HighPart;
	} u;
	LONGLONG QuadPart;
};

typedef intptr_t LPARAM;
typedef const void *LPCVOID;
typedef char *LPSTR;
typedef char *LPTSTR;
typedef intptr_t LRESULT;
typedef const GUID &REFGUID;
typedef const char *LPCTSTR;
typedef DWORD *LPDWORD;
typedef LONG *LPLONG;

enum LR
{
	LR_CREATEDIBSECTION = 1,
	LR_LOADFROMFILE = 2,
};

enum MAX
{
	MAX_PATH = 260,
};

enum MB
{
	MB_OK = 1,
	MB_ICONEXCLAMATION = 2,
};

typedef uintptr_t WPARAM;

struct MSG
{
	WPARAM wParam;
};

typedef MSG *LPMSG;

struct PAINTSTRUCT
{
};

typedef PAINTSTRUCT *LPPAINTSTRUCT;

struct PALETTEENTRY
{
	BYTE peRed;
	BYTE peGreen;
	BYTE peBlue;
	BYTE peFlags;
};

enum PM
{
	PM_REMOVE,
};

struct POINT
{
	LONG x;
	LONG y;
};

struct RECT
{
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;
};

typedef RECT *LPRECT;

struct RGNDATA
{
};

enum ROP
{
	SRCCOPY,
};

enum SC
{
	SC_KEYMENU,
	SC_TASKLIST,
};

typedef uint32_t UINT;
typedef uintptr_t UINT_PTR;

enum WA
{
	WA_INACTIVE,
};

typedef wchar_t WCHAR;

enum WM
{
	WM_ACTIVATE,
	WM_CREATE,
	WM_DESTROY,
	WM_PAINT,
	WM_SYSCOMMAND,
};

typedef LRESULT (*WNDPROC)(HWND, UINT, WPARAM, LPARAM);

struct WNDCLASSEX
{
	UINT cbSize;
	UINT style;
	WNDPROC lpfnWndProc;
	int cbClsExtra;
	int cbWndExtra;
	HINSTANCE hInstance;
	HICON hIcon;
	HCURSOR hCursor;
	HBRUSH hbrBackground;
	LPCTSTR lpszMenuName;
	LPCTSTR lpszClassName;
	HICON hIconSm;
};

enum WS
{
	WS_OVERLAPPED,
	WS_CAPTION,
	WS_CHILD,
	WS_SYSMENU,
	WS_BORDER,
	WS_MAXIMIZEBOX,
	WS_MINIMIZEBOX,
	WS_SIZEBOX,
	WS_VISIBLE,
	WS_POPUPWINDOW,
};

extern const LPCTSTR IDC_ARROW;
extern const int INFINITE;
extern const BOOL TRUE;

template <typename T>
T max(T a, T b)
{
	return a > b ? a : b;
}

template <typename T>
T min(T a, T b)
{
	return a < b ? a : b;
}

HDC BeginPaint(HWND hwnd, LPPAINTSTRUCT lpPaint);
BOOL BitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int   nYSrc, DWORD dwRop);
HDC CreateCompatibleDC(HDC hdc);
HBRUSH CreateSolidBrush(COLORREF);
HWND CreateWindow(LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
HWND CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
LRESULT DefWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL DeleteDC(HDC hdc);
BOOL DeleteFile(LPCTSTR lpFileName);
BOOL DeleteObject(HGDIOBJ hObject);
LRESULT DispatchMessage(const MSG *lpmsg);
BOOL EndPaint(HWND hWnd, const PAINTSTRUCT *lpPaint);
BYTE GetBValue(DWORD rgb);
HWND GetDesktopWindow();
BYTE GetGValue(DWORD rgb);
HMODULE GetModuleHandle(LPCTSTR lpModuleName);
int GetObject(HGDIOBJ hgdiobj, int cbBuffer,LPVOID lpvObject);
COLORREF GetPixel(HDC hdc, int nXPos, int nYPos);
BYTE GetRValue(DWORD rgb);
DWORD GetTickCount();
BOOL GetWindowRect(HWND hWnd, LPRECT lpRect);
BOOL InvalidateRect(HWND hWnd, const RECT *lpRect, BOOL bErase);
HBITMAP LoadBitmap(HINSTANCE hInstance, LPCTSTR lpBitmapName);
HCURSOR LoadCursor(HINSTANCE hInstance, LPCTSTR lpCursorName);
HICON LoadIcon(HINSTANCE hInstance, LPCTSTR lpIconName);
HANDLE LoadImage(HINSTANCE hinst, LPCTSTR lpszName, UINT uType, int cxDesired, int cyDesired, UINT fuLoad);
WORD LOWORD(DWORD dwValue);
LPTSTR MAKEINTRESOURCE(WORD wInteger);
int MessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
BOOL PeekMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT  wRemoveMsg);
void PostQuitMessage(int nExitCode);
BOOL QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);
BOOL QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
ATOM RegisterClassEx(const WNDCLASSEX *lpwcx);
COLORREF RGB(BYTE byRed, BYTE byGreen, BYTE byBlue);
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj);
LRESULT SendMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
int ShowCursor(BOOL bShow);
BOOL ShowWindow(HWND hWnd, int nCmdShow);
void Sleep(DWORD dwMilliseconds);
BOOL SUCCEEDED(HRESULT hr);
DWORD timeGetTime();
BOOL TranslateMessage(const MSG *lpMsg);
BOOL UpdateWindow(HWND hWnd);
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
void ZeroMemory(void *Destination, size_t Length);
