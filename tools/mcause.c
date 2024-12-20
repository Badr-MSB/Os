#include "mcause.h"
#include "csr_registers.h"
#include "../lib/stdio.h"
#include "../trap/handler.h"
#include "../syscon/syscon.h"

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
        printf("S-mode Exception: %s\n", cause_to_string[cause_code + 11]);
        poweroff();
    }
}

void m_trap_handler(){
    uint64_t mcause = csr_read(mcause);
    if (mcause & (1ul<<63))
    {
        switch (mcause)
        {
        case machine_timer_interrupt:
            timer_handler();
            break;
        
        default:
            printf("Interrupt: %s unhandled\n", cause_to_string[(mcause  & ~(1ul<<63)) - 1]);
            break;
        }
    }
    else
    {
        printf("M-mode Exception: %s unhandled\n", cause_to_string[(mcause  & ~(1ul<<63)) + 11]);
        poweroff();
    }
}