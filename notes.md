## Interrupts Enabling


## Timer Interupt


## CLINT of Qemu Virt

**CLINT**, stand for Core Local interrupt, 

for Qemu virt :

- CLINT Base Adress : 0x200000
- CLINT Lenght      : 0x10000
- CLINT mtimecmp    : Base Adress + 0x4000 + 8 * hartId  
- CLINT mtime       : 0x0200bff8