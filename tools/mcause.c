#include "mcause.h"
#include "../csr_registers.h"

void display_trap_cause()
{
    uint64_t mcause = csr_read(mcause);
    printf("mcause = [%d]\n", mcause);
    //  uint64_t mcause_value = csr_read(scause);
    unsigned int cause_code = mcause & 0xFFFFFFFF;
    if (cause_code >= 0x80000000)
    {
        printf("Interrupt: %s\n", cause_to_string[cause_code - 1]);
    }
    else
    {
        printf("Exception: %s\n", cause_to_string[cause_code + 11]);
    }
}