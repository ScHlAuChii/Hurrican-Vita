#include "windows.h"

#include "SDL_video.h"

#include <assert.h>

HWND CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	return SDL_CreateWindow(lpWindowName, x, y, nWidth, nHeight, SDL_WINDOW_OPENGL);
}

BOOL GetWindowRect(HWND hWnd, LPRECT lpRect)
{
	assert(hWnd == nullptr);
	
	SDL_Rect bounds = {};
	SDL_GetDisplayBounds(0, &bounds);
	
	lpRect->left = bounds.x;
	lpRect->top = bounds.y;
	lpRect->right = bounds.x + bounds.w;
	lpRect->bottom = bounds.y + bounds.h;
	
	return TRUE;
}
