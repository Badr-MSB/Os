#include <stdint.h>

#define PTE_SIZE 8               // Page Table Entry size in bytes (8 bytes)
#define PAGE_SIZE 4096           // Page size (4KB)
#define VPN_MASK 0x1FF           // Mask for 9 bits per VPN (each VPN is 9 bits)
#define VALID_BIT_MASK 0x01      // Mask for valid bit in PTE

typedef uint64_t pte_t;  // A PTE is 64-bits (8 bytes)

void satp_setup();
void map_to_virtual(uintptr_t pa, uintptr_t va, uint8_t permissions);
void walk_page_tables(uintptr_t* root_page_table, int level);
void map_memory_to_virtual(uintptr_t pa_start, uintptr_t pa_end, uintptr_t va_start, uint8_t perm);