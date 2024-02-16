#include "virt_plic.h"

void plic_set_priority(uint8_t interruptId, char priority)
{
    uint32_t *address = (uint32_t *)(VIRT_PLIC_INTERRUPT_PRIORITY_ADDR(interruptId));
    *address = priority & 0x7;
}
void plic_set_threshold(unsigned int hartId, char priority, unsigned int mode)
{
    uint32_t *adress = (uint32_t *)VIRT_PLIC_THRESHOLD_ADDR(hartId, mode);
    *adress = priority & 0x7;
}
void plic_enable(unsigned int hartId, unsigned int modeId, uint32_t interruptionId)
{
    uint32_t *adress = (uint32_t *)VIRT_TARGET_ENABLE_ADDR(hartId, modeId);
    *adress = (*adress) | (0x1 << interruptionId);
}
void plic_desable(unsigned int hartId, unsigned int modeId, uint32_t interruptId)
{
    // uint32_t *adress = (uint32_t *)VIRT_TARGET_ENABLE_ADDR(hartId, modeId);
    // *adress = (*adress) & (~(0x1 << interruptionId));
    uint32_t *base = (uint32_t *)VIRT_TARGET_ENABLE_ADDR(hartId, modeId);
    base[interruptId / 32] &= ~(1UL << (interruptId % 32));
}

uint32_t plic_claim(unsigned int hartId, unsigned int modeId)
{
    uint32_t *address = (uint32_t *)VIRT_PLIC_CLAIM_ADDR(hartId, modeId);
    return *address;
}
uint32_t plic_complete(unsigned int hartId, unsigned int modeId, unsigned int id)
{
    uint32_t *address = (uint32_t *)VIRT_PLIC_CLAIM_ADDR(hartId, modeId);
    *address = id;
}
void plic_config()
{
}