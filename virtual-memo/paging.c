#include <stdint.h>
#include <stdbool.h>
#include "paging.h"
#include "../tools/csr_registers.h"
#include "../tools/alloc.h"
#include "../lib/stdio.h"

extern char _page_table_start[];

void satp_setup(){
    uint64_t satp_value = 0;
    satp_value = (0x8ULL << 60) | ((uintptr_t)_page_table_start >> 12) ;
    // satp_value = ((uintptr_t)_page_table_start >> 12) ;
    printf("satp = %p\n", csr_read(satp));
    csr_write(satp, satp_value);
    asm volatile("sfence.vma" ::: "memory");
    //printf("satp = %p\n", csr_read(satp));
    // csr_set(sstatus,0x200);
}

// Helper function to extract the VPN[0], VPN[1], VPN[2] from a virtual address
static void extract_vpn(uint64_t va, uint64_t *vpn0, uint64_t *vpn1, uint64_t *vpn2) {
    *vpn0 = (va >> 12) & VPN_MASK;
    *vpn1 = (va >> 21) & VPN_MASK;
    *vpn2 = (va >> 30) & VPN_MASK;
}

void map_to_virtual(uintptr_t pa, uintptr_t va, uint8_t perm) {
    uint64_t vpn0, vpn1, vpn2;
    extract_vpn(va, &vpn0, &vpn1, &vpn2);

    printf("vpn0=%x,vpn1=%x,vpn2=%x\n", vpn0, vpn1, vpn2);
    // Start from the root page table
    pte_t *pte = (pte_t *)_page_table_start;

    // Iterate through page table levels (L2 -> L1 -> L0)
    for (int level = 2; level > 0; level--) {
        pte_t entry = pte[vpn2];
        printf("page tb entry = %p\n", pte);

        // Check if the entry is valid
        if (entry & VALID_BIT_MASK) {
            // If valid, move to the next level
            pte = (pte_t *)((entry >> 10) << 12);  // Extract PPN
        } else {
            // Allocate a new page table if the entry is not valid
            pte_t *new_page_table = (pte_t *)kmalloc(1 * PAGE_SIZE);
            printf("new page address : %p\n", new_page_table);
            entry = (((uintptr_t)new_page_table >> 12) << 10);  // Set PPN
            entry |= VALID_BIT_MASK;  // Set Valid bit
            printf("entry : %p\n", entry);
            pte[vpn2] = entry;  // Update the PTE
            pte = new_page_table;  // Move to the next level
        }

        // Update VPN for the next level
        if (level == 2) {
            vpn2 = vpn1;
        } else if (level == 1) {
            vpn2 = vpn0;
        }
    }

    // At the final level (L0), map the physical address to the virtual address
    pte_t final_pte = ((pa >> 12) << 10);  // Extract PPN
    final_pte |= VALID_BIT_MASK | (perm & 0x7) << 1;   // Set Valid bit & RWX
    // final_pte |= (1 << 4) | (1 << 5);      // Set Accessed (A) and Dirty (D) bits
    printf("final pte value : %p\n", final_pte);
    pte[vpn2] = final_pte; 
}

void print_PT(){
    pte_t *pte = (pte_t *)_page_table_start;
    printf("page walking\n");
    for(int i = 0; i < 512 ; i++){
        if( pte[i] & VALID_BIT_MASK)
        printf("%p = %lx\n", pte+i, pte[i]);
    }
    printf("\n");
}

void walk_page_tables(uint64_t *root_page_table, int level) {
    uint64_t *pte = root_page_table;

    for (int i = 0; i < 512; i++) {
        if (pte[i] & VALID_BIT_MASK) {
            uint64_t physical_address = (pte[i] >> 10) << 12 ;

            printf("Level %d PTE[%d]: PTE=0x%x Flags=0x%x\n", level, i, physical_address, pte[i] & 0xFF);

            // If this is not the final level, recurse into the next page table
            if (level > 0) {
                walk_page_tables((uint64_t *)physical_address, level - 1);
            }
        }
    }
}