# this file aims to create librairi called libmystdio 
# that can be user in the project by adding -L. -libmystdio

CC=riscv64-unknown-elf-gcc
CFLAGS=-ffreestanding -nostartfiles -nostdlib -nodefaultlibs
CFLAGS+=-g -Wl,--gc-sections -mcmodel=medany -march=rv64g
CFLAGS+=-Wl,--no-warn-rwx-segments
LIBIMAGE=libmystdio.o

all: printf putchar puts sprintf vprintf 
	
printf: stdio.h
	$(CC) -c stdio/printf.c $(CFLAGS) -o ../build/printf.o

putchar: stdio.h
	$(CC) -c stdio/putchar.c $(CFLAGS) -o ../build/putchar.o

puts: stdio.h
	$(CC) -c stdio/puts.c $(CFLAGS) -o ../build/puts.o

sprintf: stdio.h
	$(CC) -c stdio/sprintf.c $(CFLAGS) -o ../build/sprintf.o

vprintf: stdio.h
	$(CC) -c stdio/vprintf.c $(CFLAGS) -o ../build/vprintf.o