#pragma once

#include <errno.h>
#include <stddef.h>
#include <stdio.h>

errno_t _itoa_s(int value, char *buffer, int radix);
char *_strrev(char *str);
errno_t fopen_s(FILE **streamptr, const char *filename, const char *mode);
int fprintf_s(FILE *stream, const char *format, ...);
int sprintf_s(char *buffer, const char *format, ...);
errno_t strcat_s(char *dest, const char *src);
errno_t strcat_s(char *dest, rsize_t destsz, const char *src);
errno_t strcpy_s(char *dest, const char *src);
errno_t strcpy_s(char *dest, rsize_t destsz, const char *src);
errno_t strncat_s(char *dest, const char *src, rsize_t count);
errno_t strncpy_s(char *dest, const char *src, rsize_t count);
