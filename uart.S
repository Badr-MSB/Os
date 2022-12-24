.align 12

# a0 should contain the address of a string to print
# writeln will then write this string to the serial UART device
# followed by a newline

_write_uart_char:
	push ra
	li t1, 0x10000000
	lb t2, 0(a0)
	sb t2, 0(t1)
	pop ra
	ret

.align 12
# Write a string to UART
# a0 should contain a pointer to the string we want to print...
_write_uart:
	push ra
_write_uart_loop:
	# check that UART is free...
	li t1, 0x10000005
	lb t2, 0(t1)
	li t3, 0x20
	and t2, t3, t1
	beqz t1, _write_uart_loop
	li t1, 0x10000000
	lb t2, 0(a0)
	beqz t2, _write_uart_end
	sb t2, 0(t1)
	li t2, 1
	add a0,t2,a0
	# loop until null...
	j _write_uart_loop
_write_uart_end:
	pop ra
	ret
    
_print_hex:
	push ra
	# 64 bit value  = 8 bytes = 16 nibbles
	li a1, 15

_print_hex_loop:
	# Load Mask into T1
	li t4, 4
	mul t4, a1, t4
	sra a2, a0, t4
	li t1, 0x0F
	# t1 = Value & 0x0F
	and t1, a2, t1
	# load hextable and add the offset..
	la t2, hextable
	push a0
	push a1
	add a0, t1, t2
	call _write_uart_char
	pop a1
	pop a0
	li t1, -1
	add a1, a1, t1
	bgez a1, _print_hex_loop
	# End with a New Line
	la a0, newline
	call _write_uart
	pop ra
	ret
