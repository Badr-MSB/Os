#ifndef _PCI_H_
#define _PCI_H_

#define VIRT_PCIE_ECAM 0x30000000
#define VIRT_PCIE_MMIO 0x10000000

void list_pci_devices(void);

#endif