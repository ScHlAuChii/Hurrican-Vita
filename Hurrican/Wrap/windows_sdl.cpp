#include "windows.h"

#include "SDL_events.h"
#include "SDL_video.h"

#include <assert.h>

static WNDCLASSEX wndclass;

static void translate_window_event(LPMSG msg, const SDL_WindowEvent &e)
{
	msg->hwnd = SDL_GetWindowFromID(e.windowID);
	switch (e.event)
	{
		case SDL_WINDOWEVENT_CLOSE:
			msg->message = WM_DESTROY;
			break;
	}
}

HWND CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	return SDL_CreateWindow(lpWindowName, x, y, nWidth, nHeight, SDL_WINDOW_OPENGL);
}

LRESULT DispatchMessage(const MSG *lpmsg)
{
	SDL_Window *const window = static_cast<SDL_Window *>(lpmsg->hwnd);
	if (window == nullptr)
	{
		return 0;
	}
	
	return wndclass.lpfnWndProc(lpmsg->hwnd, lpmsg->message, lpmsg->wParam, lpmsg->lParam);
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

BOOL PeekMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT  wRemoveMsg)
{
	memset(lpMsg, 0, sizeof(*lpMsg));
	
	SDL_Event e = {};
	if (!SDL_PollEvent(&e))
	{
		return FALSE;
	}
	
	switch (e.type)
	{
		case SDL_WINDOWEVENT:
			translate_window_event(lpMsg, e.window);
			break;
			
		case SDL_QUIT:
			lpMsg->hwnd = SDL_GL_GetCurrentWindow();
			lpMsg->message = WM_DESTROY;
			break;
	}
	
	return TRUE;
}

ATOM RegisterClassEx(const WNDCLASSEX *lpwcx)
{
	wndclass = *lpwcx;
	
	return 1;
}
