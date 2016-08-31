#include "windows.h"

#include "SDL.h"

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return 1;
	}
	
	const int result = WinMain(nullptr, nullptr, argv[0], 0);
	
	SDL_Quit();
	return result;
}
