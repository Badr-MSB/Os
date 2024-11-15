#include "uart/uart.h"
#include "tools/csr_registers.h"
#include "tools/mstatus.h"
#include "pcie/pci.h"
#include "syscon/syscon.h"
#include "test/ktest.h"

extern int printf(const char *, ...);


void kmain()
{
    //***********************************//
    uart_init();
    list_pci_devices();
    
    volatile uint16_t i = 0;
    printf("Hi , it's Badr !\n");

    kmemncpy_test();

    while(i == 0);
    __builtin_unreachable();
}


