CC=riscv64-unknown-elf-gcc
CFLAGS=-ffreestanding -nostartfiles -nostdlib -nodefaultlibs
CFLAGS+=-g -Wl,--gc-sections -mcmodel=medany -march=rv64g
RUNTIME=boot/ctr0.S 
LINKER_SCRIPT=boot/kernel.ld
KERNEL_IMAGE=kernel.elf

# QEMU
QEMU=qemu-system-riscv64
MACH= virt -cpu rv64 -smp 1 -m 1G -serial mon:stdio -nographic
RUN=$(QEMU) -device VGA -machine $(MACH) 
RUN+=-bios none -kernel $(KERNEL_IMAGE) -rtc base=localtime -k fr

# Format
INDENT_FLAGS=-linux -brf -i2
# Always run targets : lib & boot 
.PHONY: lib
.PHONY: boot

all: buildfolder uart lib boot syscon pci handler boot main virt_plic mcause mstatus s_trap_handler vga
	$(CC) build/*.o $(CFLAGS) -T $(LINKER_SCRIPT) -o $(KERNEL_IMAGE) -Wl,-Map=program.map

buildfolder:
	mkdir -p build
lib:
	(cd ./lib && make all)

boot:
	(cd ./boot && make boot)

pci: pcie/pci.h
	$(CC) -c pcie/pci.c $(CFLAGS) -o build/pci.o

vga: vga.S 
	$(CC) -c vga.S -o ./build/vga.o

uart: uart/uart.h
	$(CC) -c uart/uart.c $(CFLAGS) -o build/uart.o

syscon: syscon/syscon.h
	$(CC) -c syscon/syscon.c $(CFLAGS) -o build/syscon.o

mcause: tools/mcause.h lib
	$(CC) -c tools/mcause.c $(CFLAGS) -o build/mcause.o

mstatus: tools/mstatus.h
	$(CC) -c tools/mstatus.c $(CFLAGS) -o build/mstatus.o

handler:
	$(CC) -c trap/handler.c $(CFLAGS) -o build/handler.o

virt_plic: plic/virt_plic.h
	$(CC) -c plic/virt_plic.c $(CFLAGS) -o build/virt_plic.o

s_trap_handler:
	$(CC) -c trap/supervisor_trap.c $(CFLAGS) -o build/supervisor_trap.o

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
	rm -vf *.o build/*.o *.map 
	rm -vf $(KERNEL_IMAGE)
	find . -name '*~' -exec rm -vf '{}' \;
	rm -r build