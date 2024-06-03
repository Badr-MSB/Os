CC=riscv64-unknown-elf-gcc
RUNTIME=ctr0.S 

boot: ctr0.S m_handler_crt0.S s_handler_crt0.S
	$(CC) -c $(RUNTIME) -o ../build/boot_start.o
