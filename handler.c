#include "handler.h"
#include "clint.h"
#include "uart/uart.h"

extern int printf(const char *, ...);

void timer_handler() 
{
    static uint64_t roundNumer = 0x0;
    printf("Timer interrupt handled [%d] times \n", roundNumer);
    roundNumer++;
    set_mtimecmp(roundNumer * RTC_FREQUENCY );
}