.option norvc

.section .data 

welcome: .ascii  "Welcome OsDev\0"

.section .text.init
.global _start

_start:
    csrr t0, mhartid #read the hart ID
    bnez t0, _wait   #if not 0 wait
    call _setup_uart
    la a0, welcome
    call _write_uart
    wfi

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
    # write in the output
    li t1, 0x10000000
    lb t2, 0(a0)
    beqz t2, _write_uart_end
    sb t2, 0(t1)
    li t2,1
    add a0,t2,a0
    j _write_uart

_write_uart_end:
    ret

_wait:
    wfi
