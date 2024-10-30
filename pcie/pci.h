#ifndef _PCI_H_
#define _PCI_H_

#define VGA_FRAMEBUFFER 0x000B8000
#define VGA_WIDTH 320
#define VGA_HEIGHT 200

#define VIRT_PCIE_ECAM 0x30000000
#define VIRT_PCIE_MMIO 0x10000000

void list_pci_devices(void);

void set_pixel(int x, int y, uint8_t color);

void clear_screen(uint8_t color);

void draw_example();

void draw_character(char c, int x, int y, int color);

#endif