
#include "uart/uart.h"
#include "tools/csr_registers.h"
#include "tools/mstatus.h"

extern int printf(const char *, ...);

void kmain()
{
    uart_init();
    volatile uint16_t i = 0;

    printf("Hi , it's Badr !\n");

    //asm volatile("wfi");
    while (i == 0);
    __builtin_unreachable();
}