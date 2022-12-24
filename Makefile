CC=riscv64-unknown-elf-gcc
CFLAGS=-ffreestanding -nostartfiles -nostdlib -nodefaultlibs
CFLAGS+=-g -Wl,--gc-sections -mcmodel=medany -march=rv64g
#CFLAGS+=-Wl,--no-warn-rwx-segments
RUNTIME=boot.S
LINKER_SCRIPT=kernel.ld
KERNEL_IMAGE=kernel.elf

# QEMU
QEMU=qemu-system-riscv64
MACH=virt -cpu rv64 -smp 4 -m 128M  -serial mon:stdio
RUN=$(QEMU) -nographic -machine $(MACH)
RUN+=-bios none -kernel $(KERNEL_IMAGE)

# Format
INDENT_FLAGS=-linux -brf -i2

all: uart cpu common kmain
	$(CC) *.o $(RUNTIME) $(CFLAGS) -T $(LINKER_SCRIPT) -o $(KERNEL_IMAGE)

uart:
	$(CC) -c uart.c $(CFLAGS) -o uart.o

cpu:
	$(CC) -c cpu.c $(CFLAGS) -o cpu.o

common:
	$(CC) -c common.c $(CFLAGS) -o common.o

kmain:
	$(CC) -c kmain.c $(CFLAGS) -o kmain.o

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
	rm -vf *.o
	rm -vf $(KERNEL_IMAGE)
	find . -name '*~' -exec rm -vf '{}' \;