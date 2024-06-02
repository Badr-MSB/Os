#include "../lib/stdio.h"

// handle spevisor interrupts (all interrupts exept timer one)
void supervisor_trap_handler(void){
    printf("supervisor trap handling ...");   
}