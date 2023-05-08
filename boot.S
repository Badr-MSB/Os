.option norvc 
.align 4

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

.section .data

hello: .ascii "Welcome bro !\0"
newline: .ascii "\n\0"
welcome_machine: .ascii "Welcome to machine mode\0"
welcome_supervisor: .ascii "Welcome to supervisor mode\0"
welcome_user: .ascii "Welcome to user mode"

supervisor_trap: .ascii "Supervisor warning\0"
machine_trap: .ascii "Machine warning\0"

hextable: .ascii  "0123456789ABCDEF\0"

walkingpagetables: .ascii "Walking Page Tables...\0"
endwalkingpagetables: .ascii "Walking Page Tables Complete\0"

_scrachpad: .skip 1024,0

.align 12
_stacks: .skip 8192,0

.section .text.init

.global kputs

.global _start 

_start:
    csrr t0, mhartid
    call _init_system
    bnez t0, _wfi

    la a0, hello
    call kputs
/*
    la t0, _machine_trap
    csrw mtvec, t0
    */

    la t0, _supervisor_trap
    csrw stvec, t0

   

    li t0, 0xFFFFFFFF
	csrw pmpaddr0,t0
	li t0, 0x1F
	csrw pmpcfg0,t0

    csrr t1, mstatus
    li t0, 0xFFFFE7FF
    and t1, t0, t1
    li t0, 0x800
    or t1, t1, t0
    csrw mstatus, t1
    
    li t0, 0x00000001
    slli t0, t0, 7
    and t0, t1, t0
    srai t0, t0, 6
    csrr t1, mstatus
    or t1, t1, t0
    csrw mstatus, t1
    
/*
    la t0, _supervisor_mode_entry
    csrw sepc, t0
    sret*/

    call _setup_satp

    la a0, _data_start
	la a1, _data_start
	li a2, 0x07
	call _map_to_virtual

    la a0, _stacks
	la a1, _stacks
	li a2, 0x0F
	call _map_to_virtual

    #UART Port
  
    li a0, 0x10000000
	li a1, 0x10000000
	li a2, 0x0F
	call _map_to_virtual 

    # Identity Map the Uart Functions  (F)
	la a0, _write_uart
	la a1, _write_uart
	li a2, 0x0F
	call _map_to_virtual
/*
    # writeln
    la a0, kputs
	la a1, kputs
	li a2, 0x0F
	call _map_to_virtual
*/


	# Virtual Map the Example Page (F)
	la a0, _example_page
	la a1, _example_page
	li a2, 0x0F
	call _map_to_virtual

	la a0, walkingpagetables
	call kputs

	# Print out All Page Tables
	la a0, _page_table_start
	li a1, 2
	call _walk_page_tables

	la a0, endwalkingpagetables
	call kputs

	la t0, _example_page
	csrw mepc,t0
	mret

    wfi

.include "paging.S"
.include "uart0.S"

_init_system:
    #init stack
    la a0, _stacks
    csrr t0, mhartid
    li t2, 1024
    mul t1, t0, t2
    add sp, t1, a0
    #init UART
    #1 Disable interrupts
    li t1, 0x10000001
    sb x0, 0(t1)

    #2 set the output to 8 bits, no parity, one stop bit
    li t1, 0x10000003
    li t2, 0x03
    sb t2, 0(t1)
    ret


_supervisor_mode_entry:
    push a0
    la a0, welcome_supervisor
    call kputs
    pop a0
    wfi

_supervisor_trap:
    la a0, supervisor_trap
    call kputs
    li t0, 0x30
    csrr t1, scause
    add t0, t0, t1
    la a0, _scrachpad
    sb t0, 0(a0)
    call kputs
    sret

_machine_trap:
    la a0, machine_trap
    call kputs
    li t0, 0x30
    csrr t1, mcause
    add t0, t0, t1
    la a0, _scrachpad
    sb t0, 0(a0)
    call kputs
    mret

_wfi:
    wfi

_kalloc:
	la a1, _heap_counter
	ld t0, 0(a1)

	li t1, 1
	add t0, t0, t1
	sd t0, 0(a1)

	la t1, _heap_end
	li t2, 4096
	mul t2, t0, t2
	sub a0, t1, t2
	ret

.align 12
_example_page:
	la a0, welcome_supervisor
	call kputs
	la a0, _page_table_start
	ld a0, 0(a0)
	wfi
	.skip 4096

.align 12
_page_table_start:
# Sv39 page tables contain 2^9 Page Table Entries
	.skip 4096
