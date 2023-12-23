#include "handler.h"
#include "csr_registers.h"

uint64_t roundNumer = 0x0;

extern int printf(const char *, ...);

void timer_handler()
{
    printf("Timer interrupt handled [%d] times \n", roundNumer);
    // printf("Delay choosen is %d second");
    roundNumer++;
    set_mtimecmp(roundNumer * RTC_FREQUENCY);
}