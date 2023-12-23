## CLINT of Qemu Virt

**CLINT**, stand for Core Local interrupt, used for Software and timer interrupts

for Qemu virt :

      Device        |   address                 |    size
____________________________________________________________
CLINT Base Adress   |     0x200000              |   0x10000
CLINT MSIP          | 0x200000 + 4 * hartid     |     4     
CLINT mtimecmp      |   0x204000 + 8 * hartId   |     8
CLINT mtime         |     0x0200bff8            |     8

the mtime can be readed by using the pseudo-instruction rdtime

## PLIC
**PLIC** is a programmable interrupt controller used for external interrupts. 


## Timer Interupt
