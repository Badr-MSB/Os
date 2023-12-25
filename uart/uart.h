#ifndef _UART_H
#define _UART_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

// 0x10000000 is memory-mapped address of UART according to device tree
#define UART_ADDR 0x10000000

void uart_init();

int putChar(char);

void print(char *);

void putint(int i);

void printInt(int a);

#endif