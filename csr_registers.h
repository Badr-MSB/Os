#ifndef _CSR_REGISTERS_H
#define _CSR_REGISTERS_H

#include <stdint.h>
#include <stddef.h>

#define csr_read(csr)                         \
    ({                                        \
        register uint64_t __v;                \
        __asm__ __volatile__("csrr %0, " #csr \
                             : "=r"(__v)      \
                             :                \
                             : "memory");     \
        __v;                                  \
    })
#define csr_write(csr, value)                      \
    ({                                             \
        register uint64_t __v = (uint64_t)(value); \
        __asm__ __volatile__("csrw " #csr ", %0"   \
                             :                     \
                             : "rK"(__v)           \
                             : "memory");          \
    })

// value is a bit mask that specifies bit position to be set (high bit)
#define csr_set(csr, value)                        \
    ({                                             \
        register uint64_t __v = (uint64_t)(value); \
        __asm__ __volatile__("csrs " #csr ", %0"   \
                             :                     \
                             : "rK"(__v)           \
                             : "memory");          \
    })

// value is a bit mask that specifies bit position to be cleared (high bit)
#define csr_clear(csr, value)                      \
    ({                                             \
        register uint64_t __v = (uint64_t)(value); \
        __asm__ __volatile__("csrc " #csr ", %0"   \
                             :                     \
                             : "rK"(__v)           \
                             : "memory");          \
    })

static inline void wfi()
{
    __asm__ __volatile__("wfi" ::
                             : "memory");
}

// __builtin_unreachable is used to :
// Remove dead code (that programmer knows will never be executed)
// Linearize the code by letting compiler know that the path is "cold" (similar effect is achieved by calling noreturn function)

__attribute__((noreturn)) static inline void mret()
{
    __asm__ __volatile__("mret");
    __builtin_unreachable();
}

#endif