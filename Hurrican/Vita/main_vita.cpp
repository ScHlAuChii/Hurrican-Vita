#include "windows.h"

int main(int argc, char *argv[])
{
	const int result = WinMain(nullptr, nullptr, argv[0], 0);
	
	return result;
}
