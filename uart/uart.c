#include <stdint.h>
#include <stddef.h>

#include "uart.h"

volatile uint32_t *uart = (uint32_t *)VIRT_UART0_CTRL_ADDR;

void uart_init()
{
    volatile uint8_t *ptr = (uint8_t *)UART_ADDR;
    ptr[1] = 0;
    // Set word length to 8 (LCR[1:0])
    const uint8_t LCR = 0x11;
    ptr[3] = 0x11;
    print("||============================|=> initialisation =|========================> \n");

    uint32_t uart_freq = UART0_CLOCK_FREQ;
    uint32_t baud_rate = UART0_BAUD_RATE;
    uint32_t divisor = uart_freq / baud_rate - 1;
    uart[6] = divisor;
    uart[2] = 1;
    uart[3] = 1;
    uart[4] = 2;
}

static int virt_uart_getchar()
{
    int ch = uart[1];
    if (ch < 0)
        return -1;
    return ch;
}

static int virt_uart_putchar(int ch)
{
    while (uart[0] < 0)
        ;
    return uart[0] = ch & 0xff;
}

int putChar(char c)
{
    uint8_t *ptr = (uint8_t *)UART_ADDR;
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
    return ('/' + i) + 1;
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