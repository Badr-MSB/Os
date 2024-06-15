#include "pci.h"
#include <stdint.h>
#include "../lib/stdio.h"

void list_pci_devices(void){
    uint16_t* vendor_id = (uint16_t*)VIRT_PCIE_ECAM;
    printf("Display PCI Devices");
    printf("Vendor id : 0x%x\n", vendor_id[0]);
    printf("Device id : 0x%x\n", vendor_id[1]);
}