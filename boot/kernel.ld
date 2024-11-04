OUTPUT_ARCH( "riscv" )

ENTRY( _start )

OUTPUT(kernel.elf)

MEMORY
{
  ram  (rwxa) : ORIGIN = 0x80000000, LENGTH =1024M
}

PHDRS
{
  text PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
}

SECTIONS
{
  . = 0x80000000;
  .text : {
    PROVIDE(_text_start = .);
    *(.text.init) *(.text .text.*)
    PROVIDE(_text_end = .);
  } >ram AT>ram :text

  PROVIDE(_global_pointer = .);

  .bss : {
    PROVIDE(_bss_start = .);
    *(.sbss .sbss.*) *(.bss .bss.*)
    PROVIDE(_bss_end = .);
  } >ram AT>ram :bss

  .rodata : {
    PROVIDE(_rodata_start = .);
    *(.rodata .rodata.*)
    PROVIDE(_rodata_end = .);
  } >ram AT>ram :text

  .data : {
    . = ALIGN(4096);
    PROVIDE(_data_start = .);
    *(.sdata .sdata.*) *(.data .data.*)
    PROVIDE(_data_end = .);
  } >ram AT>ram :data

  .bss : {
    PROVIDE(_bss_start = .);
    *(.sbss .sbss.*) *(.bss .bss.*)
    PROVIDE(_bss_end = .);
    . = ALIGN(2*1024*1024); /*align to 2 Mib */
    PROVIDE(_bss_end_align = .);
    PROVIDE(_heap_start = _bss_end_align);
    PROVIDE(_heap_end = _heap_start + 2M);
    PROVIDE(_free_memory_start = _heap_end);
  } >ram AT>ram :bss

  PROVIDE(_memory_start = ORIGIN(ram));
  PROVIDE(_memory_end = ORIGIN(ram) + LENGTH(ram));
  /* PROVIDE(_heap_end = _memory_end - 4096);
  PROVIDE(_heap_counter = _heap_end + 8); */

  PROVIDE(_vga_framebuffer = 0x50000000);
  PROVIDE(_vga_mmio = 0x40000000);
  /* PROVIDE(_kernel_space_end = 0x80000000 + 0x40000000 ); */

}