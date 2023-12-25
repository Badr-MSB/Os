// See LICENSE for license details.

#include <stdio.h>
#include "stdint.h"
#include "string.h"

extern void print(char *);

int puts(const char *s)
{
	size_t len = strlen(s) + 1; // +1 pour le \n
	char *out = __builtin_alloca(len);
	strncpy(out, s, len - 1);
	out[len - 1] = '\n';
	print(out);
	return 0;
}
