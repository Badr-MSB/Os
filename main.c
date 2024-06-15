
#include "uart/uart.h"
#include "tools/csr_registers.h"
#include "tools/mstatus.h"
#include "pcie/pci.h"

extern int printf(const char *, ...);

void kmain()
{
    uart_init();
    list_pci_devices();
    volatile uint16_t i = 0;

    printf("Hi , it's Badr !\n");

    while (i == 0);
    __builtin_unreachable();
}