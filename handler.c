#include "handler.h"
#include "clint.h"
#include "Uart/uart.h"

uint64_t roundNumer = 0x0;

extern int printf(const char *, ...);

void timer_handler()
{
    printf("Timer interrupt handled [%d] times \n", roundNumer);
    roundNumer++;
    set_mtimecmp(roundNumer * RTC_FREQUENCY * 2);
}