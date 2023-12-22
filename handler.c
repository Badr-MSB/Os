#include "handler.h"
#include "csr_registers.h"

uint64_t roundNumer = 0x0;

extern int printf(const char *, ...);

void timer_handler()
{
    printf("Timer interrupt handled [%d] times \n", roundNumer);
    roundNumer++;
    set_mtimecmp(roundNumer * 0x00018000);
}