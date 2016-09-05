#include "safe.h"

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>

int _itoa_s(int value, char *buffer, int radix)
{
	assert(radix == 10);
	sprintf(buffer, "%d", value);
	return 0;
}

char *_strrev(char *str)
{
	const size_t len = strlen(str);
	std::reverse(&str[0], &str[len]);
	
	return str;
}

int fopen_s(FILE **streamptr, const char *filename, const char *mode)
{
	*streamptr = fopen(filename, mode);
	return 0;
}

int fprintf_s(FILE *stream, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	const int result = vfprintf(stream, format, args);
	va_end(args);
	
	return result;
}

int sprintf_s(char *buffer, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	const int result = vsprintf(buffer, format, args);
	va_end(args);
	
	return result;
}

int strcat_s(char *dest, const char *src)
{
	strcat(dest, src);
	return 0;
}

int strcat_s(char *dest, size_t destsz, const char *src)
{
	strcat(dest, src);
	return 0;
}

int strcpy_s(char *dest, const char *src)
{
	strcpy(dest, src);
	return 0;
}

int strcpy_s(char *dest, size_t destsz, const char *src)
{
	strcpy(dest, src);
	return 0;
}

int strncat_s(char *dest, const char *src, size_t count)
{
	strncat(dest, src, count);
	return 0;
}

int strncpy_s(char *dest, const char *src, size_t count)
{
	strncpy(dest, src, count);
	return 0;
}
