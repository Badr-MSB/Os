.option norvc

.section .data 

welcome: .ascii  "Welcome \0"
iamhart: .ascii  "I am HART \0"
givingupcontrol: .ascii "Giving Up Control\0"
newline: .ascii  "\n\0"
machinemode: .ascii  "Mode: Machine \0"
interrupts_status: .ascii  "Interrupts: "
space: .ascii " \0"

_hartlock:
    .skip 8,0

#small memory for temp values
_scratchpad:
    .skip 1024,0

_stacks:
    .skip 8192,0

.section .text.init
.global _start

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
_start:
    csrr t0, mhartid
    la t1, _stacks
    li t2, 1024
    mul t3, t2, t0
    add sp, t1, t3

	bnez t0, _announce

	call _setup_uart
	la a0, welcome
	call _writeln

    call _debug_misa

    call _sanity_check
    j _announce
	wfi

_writeln:
	push ra
	call _write_uart
	la a0, newline
	call _write_uart
	pop ra
	ret

_writespace:
	push ra
	call _write_uart
	la a0, space
	call _write_uart
	pop ra
	ret
_setup_uart:
    # Disable interrupts
    li t1, 0x10000001
    sb x0, 0(t1)

    # set the output to 8 bits, no parity, one stop bit
    li t1, 0x10000003
    li t2, 0x03
    sb t2, 0(t1)
    ret

_write_uart:
    push ra
_write_uart_loop:
    li t1, 0x10000005
    lb t2, 0(t1)
    li t3, 0x20
    and t2, t3, t1
    beqz t1, _write_uart_loop 
    # write in the output 
    li t1, 0x10000000
    lb t2, 0(a0)
    beqz t2, _write_uart_end
    sb t2, 0(t1)
    li t2, 1
    add a0, t2, a0
    j _write_uart_loop

_write_uart_end:
    pop ra
    ret
 
_sanity_check:
    push ra
    csrr t0, mstatus
    li t1, 0xC00
    and t0, t1, t2
    beq t1, t2, _sanity_check_interrupts
    la a0, machinemode
    call _writeln

_sanity_check_interrupts:
    csrr t0, mstatus
    li t1, 0x8
    and t0, t1, t0
    la a0, interrupts_status
    call _write_uart

    li t3, 0x30 
    srai t2, t2, 3
    and t1, t0 , t3

    la a0, _scratchpad

    sb t1, 0(a0)
    call _writeln

_sanity_check_end:
    pop ra
    ret

_announce:
	fence
	la t0, _hartlock
	lw t0, 0(t0)
	csrr t1, mhartid
	bne t0, t1, _announce
	# Write I am HART...
	la a0, iamhart
	call _write_uart
	# Add 0x30 to the HART ID to get ASCII Number
	csrr t1, mhartid
	li t2, 0x30
	add t1, t2, t1
	# Loading our Scratchpad RAM into a0
	la a0, _scratchpad
	# Store ASCII Hart ID into scratchpad
	sb t1, 0(a0)
	call _writeln
	# Increment the HART lock
	csrr t0, mhartid
	li t1, 0x01
	add t1, t0, t1
	la t2, _hartlock
	sw t1, 0(t2)
	la t0, _hartlock
	lw t1, 0(t0)
	fence

	j _wait

_debug_misa:
    push ra
	csrr t0, misa
	# Number of Extensions to Check
	li t1, 26
	# Counter
	li t2, 0
	# Mask
	li t3, 1
	_debug_misa_extension_start:
	and t4, t0, t3
	beqz t4, _debug_misa_extension_inc

	# Load ASCII 'A' into T4
	li t4, 0x41
	add t4, t4, t2

	# Loading our Scratchpad RAM into a0
	la a0, _scratchpad
	# Store ASCII Extension Value
	sb t4, 0(a0)
	push t0
	push t1
	push t2
	push t3
	call _writespace
	pop t3
	pop t2
	pop t1
	pop t0



	_debug_misa_extension_inc:
	srai t0, t0, 1
	add t2, t2, t3	
	bne t1, t2, _debug_misa_extension_start

	la a0, newline
	call _write_uart
	pop ra
    ret

_wait:
    wfi
