#include "plic/virt_plic.h"

void boot_start()
{
    // plic_desable(0, 0, 10);
    asm volatile("mret");
}