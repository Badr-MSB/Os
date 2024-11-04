#include "uart/uart.h"
#include "tools/csr_registers.h"
#include "tools/mstatus.h"
#include "pcie/pci.h"
#include "syscon/syscon.h"
#include "tools/alloc.h"

extern int printf(const char *, ...);

extern char _memory_start[];
extern char _memory_end[]; 


char src[] = "deadbeaf deadbea  a ";
char dst[21] = {0};

void func(){
    kmemcpy(src,dst,21);
    for(int i = 0; i<21; i++){
        if(src[i] != dst[i]){
            printf("there is an error in memcpy\n");
            return;
        }
    }
    printf("memcpy seems correct\n");
    return;
}

void kmain()
{
    //*********** Dump memory ************//
    uint64_t * memory_start = (uint64_t*)_memory_start;
    uint64_t * memory_end = (uint64_t*)_memory_end;

    printf("memory start : %x \n", memory_start);
    printf("memory end : %x\n", memory_end);
    printf("memory size : %x\n", memory_end - memory_start);

    //***********************************//
    uart_init();
    list_pci_devices();
    
    // draw_example();
    volatile uint16_t i = 0;
    func();
    printf("Hi , it's Badr !\n");

    while (i == 0);
    __builtin_unreachable();
}


