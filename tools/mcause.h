#ifndef _MCAUSE_H_
#define _MCAUSE_H_

#include <stdint.h>
#include "../lib/stdio.h"

enum cause
{
    // interrupts
    supervisor_sfotware_interrupt = 0x8000000000000001,
    Reserved2,
    machine_sfotware_interrupt = 0x8000000000000003,
    Reserved4,
    supervisor_timer_interrupt = 0x8000000000000005,
    Reserved6,
    machine_timer_interrupt = 0x8000000000000007,
    Reserved8,
    supervisor_external_interrupt = 0x8000000000000009,
    Reserved10,
    machine_external_interrupt = 0x800000000000000b,

    // exceptions
    Instruction_address_misaligned = 0x0,
    Instruction_access_fault = 0x1,
    Illegal_instruction = 0x2,
    Breakpoint = 0x3,
    Load_address_misaligned = 0x4,
    Load_access_fault = 0x5,
    Store_AMO_address_misaligned = 0x6,
    Store_AMO_access_fault = 0x7,
    Environment_call_from_U_mode = 0x8,
    Environment_call_from_S_mode = 0x9,
    Reserved_exception_10,
    Environment_call_from_M_mode = 0x0b,
    Instruction_page_fault = 0x0c,
    Load_page_fault = 0x0d,
    Reserved_exception_14,
    Store_AMO_page_fault = 0x0f
};

const char *cause_to_string[] = {
    "supervisor_sfotware_interrupt",
    "Reserved",
    "machine_sfotware_interrupt",
    "Reserved",
    "supervisor_timer_interrupt",
    "Reserved",
    "machine_timer_interrupt",
    "Reserved",
    "supervisor_external_interrupt",
    "Reserved",
    "machine_external_interrupt",

    // exceptions
    "Instruction_address_misaligned",
    "Instruction_access_fault",
    "Illegal_instruction",
    "Breakpoint",
    "Load_address_misaligned",
    "Load_access_fault",
    "Store_AMO_address_misaligned",
    "Store_AMO_access_fault",
    "Environment_call_from_U_mode",
    "Environment_call_from_S_mode",
    "Reserved",
    "Environment_call_from_M_mode",
    "Instruction_page_fault",
    "Load_page_fault",
    "Reserved",
    "Store_AMO_page_fault"};

void m_display_trap_cause();
void s_display_trap_cause();
void m_trap_handler();

#endif
