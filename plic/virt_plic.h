#ifndef _VIRT_PLIC_H_
#define _VIRT_PLIC_H_

#include <stdint.h>

#define VIRT_PLIC_BASE 0x0c000000
#define VIRT_PLIC_PENDING_BASE 0x0c001000
#define VIRT_PLIC_ENABLE_BASE 0x0c002000
// [0:2] : RW - [3:31] WIRI
#define VIRT_PLIC_THRESHOLD_BASE 0x0c200000

#define VIRT_PLIC_MODE_MACHINE 0
#define VIRT_PLIC_MODE_SUPERVISOR 1
#define VIRT_PLIC_MODE_USER 3

// priorities are given by a number from 0 to 7
#define VIRT_PLIC_INTERRUPT_PRIORITY_ADDR(interrupt_id) \
    (VIRT_PLIC_BASE + 0x4 * interrupt_id)
// M-mode id = 0, S-mode id = 1. 32 bits RW register to enable 32 interrupt
#define VIRT_TARGET_ENABLE_ADDR(hartId, modeId) \
    (VIRT_PLIC_ENABLE_BASE + 0x100 * hartId + 0x80 * modeId)

#define VIRT_PLIC_THRESHOLD_ADDR(hartId, modeId) \
    (VIRT_PLIC_THRESHOLD_BASE + 0x200 * hartId + 0x100 * modeId)

#define VIRT_PLIC_CLAIM_ADDR(hartId, modeId) \
    (VIRT_PLIC_THRESHOLD_ADDR(hartId, modeId) + 0x4)

void plic_set_priority(uint8_t, char);
void plic_set_threshold(unsigned int hart, char priority, unsigned int mode);
void plic_enable(unsigned int hart, unsigned int mode, uint32_t interruptionId);
void plic_desable(unsigned int hart, unsigned int mode, uint32_t interruptionId);
uint32_t plic_claim(unsigned int hartId, unsigned int modeId);
uint32_t plic_complete(unsigned int hartId, unsigned int modeId, unsigned int id);

void plic_config();

#endif