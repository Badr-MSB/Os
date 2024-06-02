#pragma once

#include <stdarg.h>
#include <stddef.h>

#define  die(str, ...) ({ printf("%s:%d: " str "\n", __FILE__, __LINE__, ##__VA_ARGS__);})
#define fprintf(f, ...) printf(__VA_ARGS__)

int printf(const char *, ...);
int puts(const char *);
int sprintf(char *, const char *, ...);
int snprintf(char *, size_t, const char *, ...);
int vprintf(const char *, va_list);
int vsprintf(char *, const char *, va_list);
int vsnprintf(char *, size_t, const char *, va_list);
