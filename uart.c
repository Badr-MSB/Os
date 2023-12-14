#include <stdint.h>
#include <stddef.h>

#include "uart.h"

void uart_init()
{
    volatile uint8_t *ptr = (uint8_t *)0x10000000;
    ptr[1] = 0;
    // Set word length to 8 (LCR[1:0])
    const uint8_t LCR = 0b11;
    ptr[3] = 0b11;
    print("============================|=> initialisation =|========================> \n");
}

int putChar(char c)
{
    volatile uint8_t *ptr = (uint8_t *)UART_ADDR;
    ptr[0] = c;
    return 1;
}

// entier entre 0 et 9
void putint(int i)
{
    char c = '/';
    putChar(c + i + 1);
}
char intTochar(int i)
{
    return '/' + i + 1;
}
void printInt(int a)
{
    while (a > 9)
    {
        putint(a % 10);
        a = a / 10;
    }
    putint(a);
    putChar('\n');
}
void print(char *str)
{
    while (*str != '\0')
    {
        putChar(*str);
        str++;
    }
}