#include "uart/uart.h"
#include "tools/csr_registers.h"
#include "tools/mstatus.h"
#include "tools/memory_layout.h"
#include "pcie/pci.h"
#include "syscon/syscon.h"
#include "test/ktest.h"
#include "virtual-memo/paging.h"
#include "lib/stdio.h"

extern char _data_start[];
extern char _page_table_start[];

void kmain()
{
    //*********** Dump memory ************//
    uint64_t* memory_start = (uint64_t*)_memory_start;
    uint64_t* memory_end = (uint64_t*)_memory_end;

    printf("memory start : %x \n", memory_start);
    printf("memory end : %x\n", memory_end);
    printf("memory size : %x\n", memory_end - memory_start);

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
    // text 
    map_to_virtual((uintptr_t)0x80000000ULL,(uintptr_t)0x80000000ULL, 0x5);
    map_to_virtual((uintptr_t)0x80001000ULL,(uintptr_t)0x80001000ULL, 0x5);
    map_to_virtual((uintptr_t)0x80002000ULL,(uintptr_t)0x80002000ULL, 0x5);
    //bss
    map_to_virtual((uintptr_t)0x80003000ULL,(uintptr_t)0x80003000ULL, 0x7);
    map_to_virtual((uintptr_t)0x80004000ULL,(uintptr_t)0x80004000ULL, 0x7);
    
    // // // rodata & data
    // map_to_virtual((uintptr_t)0x80200000ULL,(uintptr_t)0x80202000ULL, 0x7);
    // map_to_virtual((uintptr_t)0x80201000ULL,(uintptr_t)0x80202000ULL, 0x7);
    // map_to_virtual((uintptr_t)0x80202000ULL,(uintptr_t)0x80202000ULL, 0x7);
    // map_to_virtual((uintptr_t)0x80203000ULL,(uintptr_t)0x80203000ULL, 0x7);
    // map_to_virtual((uintptr_t)0x80204000ULL,(uintptr_t)0x80204000ULL, 0x7);
    // map_to_virtual((uintptr_t)0x80205000ULL,(uintptr_t)0x80205000ULL, 0x7);
    // map_to_virtual((uintptr_t)0x80206000ULL,(uintptr_t)0x80206000ULL, 0x7);
    // map_to_virtual((uintptr_t)0x80207000ULL,(uintptr_t)0x80207000ULL, 0x7);
    // map_to_virtual((uintptr_t)0x80208000ULL,(uintptr_t)0x80208000ULL, 0x7);
    // map_to_virtual((uintptr_t)0x80209000ULL,(uintptr_t)0x80209000ULL, 0x7);
    
    walk_page_tables((uintptr_t)_page_table_start, 2);
    printf("Setting satp\n");
    satp_setup();

    while(1);
    __builtin_unreachable();
}


