#include "pci.h"
#include <stdint.h>
#include "../lib/stdio.h"

void list_pci_devices(void){
    int block = 0;
    uint16_t* base_add = (uint16_t*)VIRT_PCIE_ECAM;
    while( *base_add != 0xffff  ){
        printf("vandor : 0x%x  &  Device : 0x%x\n",base_add[0] ,base_add[1] );
        base_add += 4*4096;
    }
}