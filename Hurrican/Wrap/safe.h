#pragma once

#include <stddef.h>
#include <stdio.h>

int _itoa_s(int value, char *buffer, int radix);
char *_strrev(char *str);
int fopen_s(FILE **streamptr, const char *filename, const char *mode);
int fprintf_s(FILE *stream, const char *format, ...);
int sprintf_s(char *buffer, const char *format, ...);
int strcat_s(char *dest, const char *src);
int strcat_s(char *dest, size_t destsz, const char *src);
int strcpy_s(char *dest, const char *src);
int strcpy_s(char *dest, size_t destsz, const char *src);
int strncat_s(char *dest, const char *src, size_t count);
int strncpy_s(char *dest, const char *src, size_t count);
