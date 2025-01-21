# compiling user apps

LINKER= user_linker.ld
CC=riscv64-unknown-elf-gcc
LD=riscv64-unknown-elf-ld
CFLAGS=-ffreestanding -nostartfiles -nostdlib -nodefaultlibs
CFLAGS+=-g -Wl,--gc-sections -mcmodel=medany -march=rv64g

apps: user.h
	$(CC) -c user.c -o ../build/user_app.bin.o $(CFLAGS)