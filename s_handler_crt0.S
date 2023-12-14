
_s_ct_switch:
    csrr t0, scause
    li t1, 5
    li t2, (1 << 63)
    or t1, t1 , t2
    and t0 , t0 , t1
    #bne t0,t1 , _sret

    la a0, s_context_switch_msg
    call print

    push x1
    push x2
    push x3
    push x4
    push x5
    push x6
    push x7 
    push x8
    push x9
    push x10
    push x11
    push x12
    push x13
    push x14
    push x15
    push x16
    # ...
    call timer_handler
    # ...
    pop x16
    pop x15
    pop x14
    pop x13
    pop x12
    pop x11
    pop x10
    pop x9
    pop x8 
    pop x7
    pop x6
    pop x5
    pop x4
    pop x3
    pop x2
    pop x1
 
    sret # pc <- mepc , disable mask 
_sret:
    sret
