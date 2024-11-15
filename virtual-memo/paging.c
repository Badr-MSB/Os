#include <stdint.h>
#include "paging.h"
#include "../tools/csr_registers.h"

extern char _page_table_start[];

void satp_setup(){
    uint64_t satp_value = 0;
    satp_value = (0x8ULL << 60) | ((uintptr_t)_page_table_start >> 12) ;
    csr_write(satp, satp_value);
}

