.option norvc 
.align 8

.bss 
.macro push reg
    sd \reg, 0(sp)
    li t0, -8
    add sp, sp, t0
.endm

.macro pop reg
    li t0, 8
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

.section .bss
    .align 4
    .globl _scrachpad
    _scrachpad: .skip 1024,0

    .align 4
    .globl _stacks
    _stacks: .skip 2048

    # .align 4
    # .globl _mtrap_stacks
    # _mtrap_stacks: .skip 2048

    
.section .text.init

.globl _start

_start:

    #Set up stack // 4 hart sp -> *******
    csrr t0, mhartid
    la a0, _stacks
    li t2, 512
    mul t1, t0, t2
    add sp, t1, a0
    
    # place machine trap stack on m mscratch
    # la  t1, _mtrap_stacks + 2048
    # csrw mscratch, t1

    csrw satp, x0                                # Disable address translation (pagging).
    #send all harts to wait for interruption except hart 0
    csrr t0, mhartid
    bnez t0, _wfi

    csrw mie, zero                              # desable interrupt

    call dispaly_misa
    #config interrupt processing
    la t0 , _m_ct_switch
    csrw mtvec, t0

    la t0, _s_ct_switch
    csrw stvec, t0

    call display_current_mode                    # current mode

    li    t0, 0x000008a0                        #previous interrupt enable for M&S , defining S-mode as MPP
    csrs  mstatus, t0
    call  dispaly_mstatus


    ######## Set supervisor entry
    la t0, kmain
    csrw mepc, t0

    # Allow access to all memory (it's an obligation to use S-Mode)
    li a0, -1              
    csrw pmpaddr0 , a0

    li a0 , (0x18 | 0x04 | 0x02 | 0x01)
    csrw pmpcfg0 , a0

    # timer interrupts (M mode)
    # Setting mtime to 0
    la t0, MTIME
    li t1, 0
    sd t1,0(t0)
    # setting mtimecmp
    la t0, MTIMECMP 
    li t1, 20000000
    sd t1, 0(t0)
   
    # enabling MTI  
    li t0, 0x00000080
    csrs mie, t0

    #delegating MTI to S-Mode
    li      t0, 0x80
    csrs    mideleg, t0

    //la ra, _wfi
    mret
    
_wfi:
    wfi

.include "m_handler_crt0.S"
.include "s_handler_crt0.S"  
