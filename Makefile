CC=riscv64-unknown-elf-gcc
CFLAGS=-ffreestanding -nostartfiles -nostdlib -nodefaultlibs
CFLAGS+=-g -Wl,--gc-sections -mcmodel=medany -march=rv64g
CFLAGS+=-Wl,--no-warn-rwx-segments
RUNTIME=boot.S 
LINKER_SCRIPT=kernel.ld
KERNEL_IMAGE=kernel.elf

# QEMU
QEMU=qemu-system-riscv64
MACH=virt -nographic -cpu rv64 -smp 1 -m 2048M -serial mon:stdio
RUN=$(QEMU) -device VGA -machine $(MACH)
RUN+=-bios none -kernel $(KERNEL_IMAGE) -rtc base=localtime -k fr

# Format
INDENT_FLAGS=-linux -brf -i2

all: uart handler main boot
	$(CC) build/*.o $(CFLAGS) -T $(LINKER_SCRIPT) -o $(KERNEL_IMAGE) -Wl,-Map=program.map

boot: boot.S 
	$(CC) $(RUNTIME) -c $(CFLAGS) -o build/boot.o

uart: Uart/uart.h
	$(CC) -c Uart/uart.c $(CFLAGS) -o build/uart.o

handler:
	$(CC) -c handler.c $(CFLAGS) -o build/handler.o
main:
	$(CC) -c main.c $(CFLAGS) -o build/main.o

run: all
	$(RUN)

debug: all
	$(RUN) -s -S

format:
	find . -name '*.h' -exec indent $(INDENT_FLAGS) '{}' \;
	find . -name '*.c' -exec indent $(INDENT_FLAGS) '{}' \;
	find . -name '*.h' -exec sed -i -r 's/(0) (b[01]+)/\1\2/g' '{}' \;
	find . -name '*.c' -exec sed -i -r 's/(0) (b[01]+)/\1\2/g' '{}' \;
	echo "You should now \`make run\` to confirm the project still builds and runs correctly"

clean:
	rm -vf *.o build/*.o lib/*.o
	rm -vf $(KERNEL_IMAGE)
	find . -name '*~' -exec rm -vf '{}' \;