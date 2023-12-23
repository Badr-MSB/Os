#ifndef _HANDLER_H_
#define _HANDLER_H_

#include "Uart/uart.h"

#define CLINT_MTIME 0x0200bff8
#define CLINT_MTIMECMP 0x02004000
#define CLINT_STIME 0xc000
#define CLINT_STIMECMP 0xc008
#define CLINT_UTIME 0xd000
#define CLINT_UTIMECMP 0xd008

#define RTC_FREQUENCY 10000000 // 10 MHz cycle each ~= 40 ns

#define set_mtimecmp(value)                                \
    ({                                                     \
        *(uint64_t *)(CLINT_MTIMECMP) = (uint64_t)(value); \
    })

#define set_mtime(value)                                \
    ({                                                  \
        *(uint64_t *)(CLINT_MTIME) = (uint64_t)(value); \
    })

#define get_mtimecmp() (*(uint64_t *)(CLINT_MTIMECMP))

#define get_mtime() (*(uint64_t *)(CLINT_MTIME))

void timer_handler();

#endif