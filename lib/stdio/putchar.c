
#include "../stdio.h"

extern int putChar(char *);

int putchar(int ch)
{
	if (1 == (putChar((char *)&ch)))
		return ch;
	else
		return -1;
}
