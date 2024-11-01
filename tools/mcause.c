#include "mcause.h"
#include "csr_registers.h"
#include "../lib/stdio.h"

void m_display_trap_cause()
{
    uint64_t mcause_value = csr_read(mcause);
    printf("mcause = [%lx] ", mcause_value);

    uint64_t cause_code = mcause_value & 0x7FFFFFFFFFFFFFFF;
    if (mcause_value & ( 1ul << 63) == (1ul << 63))
    {
        printf("Interrupt: %s\n", cause_to_string[cause_code - 1]);
    }
    else
    {
        printf("Exception: %s\n", cause_to_string[cause_code + 11]);
    }

}
void s_display_trap_cause()
{
    uint64_t scause = csr_read(scause);
    printf("scause = [%lx]\n", scause);
    //  uint64_t mcause_value = csr_read(scause);
    unsigned int cause_code = scause & 0xFFFFFFFF;
    if (cause_code >= (1ul << 63  ))
    {
        printf("Interrupt: %s\n", cause_to_string[cause_code - 1]);
    }
    else
    {
        printf("Exception: %s\n", cause_to_string[cause_code + 11]);
    }
}