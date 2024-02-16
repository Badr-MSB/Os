#ifndef _UART_H
#define _UART_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

// 0x10000000 is memory-mapped address of UART according to device tree
#define UART_ADDR 0x10000000

#define UART0_CLOCK_FREQ 0x00011000
#define UART0_BAUD_RATE 0x00011100

#define CEP_CLINT_CTRL_ADDR 0x66660000
#define CEP_CLIC_CRTL_ADDR 0x66660001
#define CEP_UART0_CTRL_ADDR 0x66660010
#define CEP_POWEROFF_CTRL_ADDR 0x66660002

static volatile int *uart = (int *)0x66660010;

void uart_init();

int putChar(char);

void print(char *);

void putint(int i);

void printInt(int a);

#endif