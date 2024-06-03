# CLINT in Qemu Virt

**CLINT**, stand for Core Local interrupt, used for Software and timer interrupts (internal)

For Qemu virt :

| Device              |   address               |    size   |
|---------------------|-------------------------|-----------|
| CLINT               |     0x200000            |  0x10000  |
| CLINT MSIP          | 0x200000 + 4 * hartid   |     4     |
| CLINT mtimecmp      |   0x204000 + 8 * hartId |     8     |
| CLINT mtime         |     0x0200bff8          |     8     |

the mtime can be readed by using the pseudo-instruction rdtime

## Timer Interupt à la RISC-V

The machine mode timer interrupt is generated when:
- mie in mstatus in enabled
- MTIE in mie is enabled
- mtime > mtimecmp

N.B : machine timer interrupts connot be delegated to Supervisor mode. To do so, unse sofware interrupts.

## Software Interrupt

[Comming Soon]

# PLIC
**PLIC**, stands for Platform Level Interrupt Controller, is a programmable interrupt controller used for external interrupts. 

## How it works
When a device is seeking for attention :
- Source interrupt pending bit (in the **PLIC**) is set to 1.
- All enable cores, for this particular interrupt, are notified.
At this stage, the cores are aware that an "External" (asyncronous) interrupt is pending, and if interrupts are enabled a trap occurs.
Then :
- The trap handler will CLAIM the interrupt
This is done by reading the coresponding memory mapped register from the **PLIC**. 
Then:
- The **PLIC** returns the id of the interrupting device in response for thet load (read).
- The interrupt pending bit is cleared.
- when the handler tasks are completed the store operation the coresponding memry-mapped resgister notify the **PLIC** that the interrupt in being handled.

In the multicore sys, the read operation returns the interrupting device id for one core (the one that will handle it).

| Device              |   address               |    size                       |
|---------------------|-------------------------|-------------------------------|
| PLIC                |   0xc000000             |0x2000 + 0x1000 * NumberOfHarts|


for more informations : https://github.com/riscv/riscv-plic-spec/blob/master/riscv-plic.adoc

## APLIC

[Comming Soon]