#include <stdint.h>
#include <stddef.h>

#include "uart/uart.h"
#include "csr_registers.h"
#include "tools/mstatus.h"

void kmain()
{
    uart_init();

    print("Hi , it's Badr !\n");
    dispaly_mstatus();
    display_current_mode();

    // enable UART for keyboard
}