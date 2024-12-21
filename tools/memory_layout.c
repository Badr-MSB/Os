#include <stdint.h>
#include "memory_layout.h"
#include "../lib/stdio.h"

extern char _text_start[];
extern char _text_end[];
extern char _bss_start[];
extern char _bss_end[];
extern char _rodata_start[];
extern char _rodata_end[];
extern char _data_start[];
extern char _data_end[];
extern char _heap_start[];
extern char _heap_end[];

void memory_layout(void){
    printf("Memory Layout\n");

    printf("text start : %p\n", (uintptr_t)_text_start );
    printf("text end : %p\n", (uintptr_t)_text_end );

    printf("bss start : %p\n", (uintptr_t)_bss_start );
    printf("bss end : %p\n", (uintptr_t)_bss_end );

    printf("Heap start : %p\n", (uintptr_t)_heap_start );
    printf("Heap end : %p\n", (uintptr_t)_heap_end );

    printf("rodata start : %p\n", (uintptr_t)_rodata_start );
    printf("rodata end : %p\n", (uintptr_t)_rodata_end );

    printf("data start : %p\n", (uintptr_t)_data_start );
    printf("data end : %p\n", (uintptr_t)_data_end );

    printf("////////////////////////////////////\n");
}