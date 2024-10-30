#include "mstatus.h"
#include "../lib/stdio.h"
#include "csr_registers.h"

void display_current_mode()
{
    uint64_t mstatus = csr_read(sstatus);
    uint64_t mpp = ((mstatus & (0b11 << 11)) >> 11);
    switch (mpp)
    {
    case 0:
        printf("Machine Mode\n");
        break;
    case 1:
        printf("Supervisor Mode\n");
    case 2:
        printf("User Mode\n");
    default:
        printf("Unknown mode\n");
        break;
    }
}
void dispaly_mstatus()
{
    printf("mstatus = [%lx]\n", csr_read(mstatus));
}
void dispaly_sstatus()
{
    printf("sstatus = [%lx]\n", csr_read(sstatus));
}

void dispaly_misa()
{
    printf("misa = [%lx]\n", csr_read(misa));
}
