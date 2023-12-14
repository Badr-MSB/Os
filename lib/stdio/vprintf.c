// See LICENSE for license details.

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>

extern int print(char *str);

#define alloca(sz) __builtin_alloca(sz)

int vprintf(const char *s, va_list vl)
{
    char *out;
    size_t n = -1;
    int res = vsnprintf(NULL, n, s, vl);
    out = alloca(res + 1);
    vsnprintf(out, res + 1, s, vl);
    print(out);
    return res;
}
