.option norvc 
.align 8

.bss 
.macro push reg
    sd \reg, 0(sp)
    li t0, 8
    add sp, sp, t0
.endm

.macro pop reg
    li t0, -8
    add sp, sp, t0
    ld \reg, 0(sp)
.endm

.section .rodata
hello: .ascii "Shalom\n\0"
message: .ascii "Salam, it's me\n\0" 
m_context_switch_msg: .ascii "M-Mode Switching Context\n\0"
s_context_switch_msg: .ascii "S-Mode Switching Context\n\0"

.equ MTIMECMP, 0x2004000
.equ MTIME, 0x0200bff8
.equ MSTATUS_MPP_MASK ,0x0000000F
.equ MSTATUS_MPP_SHIFT, 11
.equ MSTATUS_SPP_MASK ,0x00000008
.equ MSTATUS_MIE_MASK ,0x00000008
.equ MSTATUS_SPIE_MASK, 0x00000020
.equ MSTATUS_UIE_MASK ,0x00000010

.section .data
    .align 4
    .globl _scrachpad
    _scrachpad: .skip 1024,0

    .align 4
    .globl _stacks
    _stacks: .skip 2048,0

.section .text.init

.globl _start
.globl _ct_switch

_start:

    #Set up stack // 4 hart sp -> *******
    csrr t0, mhartid
    la a0, _stacks
    li t2, 512
    mul t1, t0, t2
    add sp, t1, a0
    
    #send all harts to wait for interruption except hart 0
    csrr t0, mhartid
    bnez t0, _wfi

    #config interrupt processing
    la t0 , _m_ct_switch
    csrw mtvec, t0

    la t0, _s_ct_switch
    csrw stvec, t0

    call display_current_mode                    # current mode

    li    t0, 0x00000820  #Enabling PMP mode, enabling SIE & previous interrupt enable + defining S-mode as MPP
    csrs  mstatus, t0
    call  dispaly_mstatus

    csrw satp, x0                                # Disable address translation.

    la a0, message
    call print

    csrw mie, zero                                 # desable interrupt


   
    ######## Set supervisor entry
    la t0, kmain
    csrw mepc, t0

    li a0, -1                                     # Allow access to all memory
    csrw pmpaddr0 , a0

    li a0 , (0x18 | 0x04 | 0x02 | 0x01)
    csrw pmpcfg0 , a0

    # # timer interrupts (M and S mode)
    # # + machine level external interrupts (it will be usefull for keyboard and mouse interrrupts) 
    # li t0, 0x000008a0
    csrrs x0, mie, t0

    #delegating timer interrupt to S-Mode
    # li      t0, 0x20
    # csrs    mideleg, t0

    #Setting mtime to 0
    la t0, MTIME
    li t1, 0
    sd t1,0(t0)
   
    # setting mtimecmp
    la t0, MTIMECMP 
    li t1, 20000000
    sd t1, 0(t0)

    #jalr boot_start
    # If kmain returns, wfi
    la   ra,_wfi
    mret
    
_wfi:
    wfi
    j _wfi

.include "m_handler_crt0.S"
.include "s_handler_crt0.S"  
