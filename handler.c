#include "handler.h"
#include "csr_registers.h"

int roundNumer = 1;

extern int printf(const char *, ...);

void timer_handler()
{
    printf("printer %d\n", roundNumer);
    roundNumer++;
    set_mtimecmp(roundNumer * 0x1800000);
}