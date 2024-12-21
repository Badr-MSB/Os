#include "uart/uart.h"
#include "tools/csr_registers.h"
#include "tools/mstatus.h"
#include "tools/memory_layout.h"
#include "pcie/pci.h"
#include "syscon/syscon.h"
#include "test/ktest.h"
#include "virtual-memo/paging.h"
#include "lib/stdio.h"

extern char _text_start[];
extern char _text_end[];
extern char _bss_start[];
extern char _data_end[];
extern char _page_table_start[];

void kmain()
{
    //***********************************//
    uart_init();
    init_mem_alloc_ui32();
    list_pci_devices();
    
    memory_layout();

    printf("Hi , it's Badr !\n");

    kmemncpy_test();

    printf("mapping to virtual\n");

    printf("page table start : %p\n",(uintptr_t)_page_table_start);

    // UART Port
    map_to_virtual((uintptr_t)0x10000000ULL,(uintptr_t)0x10000000ULL, 0x7);

    map_memory_to_virtual((uintptr_t)_text_start, (uintptr_t)_text_end, (uintptr_t)0x80000000ULL, 0x5);
    map_memory_to_virtual((uintptr_t)_bss_start, (uintptr_t)_data_end, (uintptr_t)0x80003000ULL, 0x7);

    walk_page_tables((uintptr_t)_page_table_start, 2);
    
    printf("Setting satp\n");
    satp_setup();

    printf("LOOP\n");

    while(1);
    __builtin_unreachable();
}


