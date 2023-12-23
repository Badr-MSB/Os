#include <stdint.h>
#include <stddef.h>

#include "Uart/uart.h"
#include "csr_registers.h"

void kmain()
{
    uart_init();

    print("Hi , it's Supervisor Badr !\n");
}