#include "alloc.h"

/*kernel heap size is of size 2Mib*/
extern const char _heap_start[];
extern const char _heap_end[];
struct mem_struct{
    struct mem_struct* next_pst;
    struct mem_struct* prev_pst;
    uint32_t size_ui32;
    uint8_t  is_free_ui8;
    uint32_t magic_ui32;
}mem_struct;
uint64_t g_kernel_heap_size_ui64 = 0;
uint64_t g_kernel_heap_start_ui64 = 0;
uint64_t g_kernel_heap_end_ui64 = 0;
uint64_t g_kernel_heap_cursor_ui64 = 0;
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + prev | next | size | isfree | magic |          data          | magic +
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int32_t init_mem_alloc_ui32()
{
    uint64_t l_heap_start_ui64 = (uint64_t)_heap_start;
    uint64_t l_heap_end_ui64 = (uint64_t)_heap_end;
    uint64_t l_heap_size_ui64 = l_heap_end_ui64 - l_heap_start_ui64;
    struct mem_struct l_memory_st = (struct mem_struct){0};

    if (l_heap_start_ui64 % (2 * MiB))
        return -1;
    if (l_heap_end_ui64 % (2 * MiB))
        return -1;
    if (!l_heap_size_ui64)
        return -1;

    g_kernel_heap_size_ui64 = l_heap_start_ui64;
    g_kernel_heap_start_ui64 = l_heap_end_ui64;
    g_kernel_heap_end_ui64 = l_heap_size_ui64;
    g_kernel_heap_cursor_ui64 = l_heap_start_ui64;

    return 0;
}

void *kmalloc(uint32_t f_size_ui32)
{
    /*find if there is enough place*/
    uint64_t l_returned_pointer_ui64 = g_kernel_heap_cursor_ui64;
    g_kernel_heap_cursor_ui64 += f_size_ui32;
    return (void *)l_returned_pointer_ui64;
}

/* there is no free */

void kmemncpy(void *f_src_pvd, void *f_dst_pvd, uint32_t f_size_ui32)
{
    uint64_t *l_src_pui64 = f_src_pvd;
    uint64_t *l_dst_pui64 = f_dst_pvd;
    uint8_t *l_src_pui8 = f_src_pvd + f_size_ui32;
    uint8_t *l_dst_pui8 = f_dst_pvd + f_size_ui32;
    uint32_t l_reminder_bytes_ui32 = f_size_ui32 % 8;

    if ((uint64_t)l_src_pui64 <= (uint64_t)l_dst_pui64 && (uint64_t)l_src_pui64 + f_size_ui32 > (uint64_t)l_dst_pui64)
    {
        while ((uint64_t)f_src_pvd <= (uint64_t)l_src_pui8)
        {
            *(--l_dst_pui8) = *(--l_src_pui8);
        }
    }
    else
    {
        for (int i = 0; i < f_size_ui32 / 8; i++)
        {
            *(l_dst_pui64++) = *(l_src_pui64++);
        }

        for (int i = 0; i < l_reminder_bytes_ui32 / 4; i++)
        {
            *(uint32_t *)l_dst_pui64 = *(uint32_t *)l_src_pui64;
            l_dst_pui64 = (uint64_t*)((uint32_t *)l_dst_pui64 + 1);
            l_src_pui64 = (uint64_t*)((uint32_t *)l_src_pui64 + 1);
        }

        l_reminder_bytes_ui32 = l_reminder_bytes_ui32 % 4;

        for (int i = 0; i < l_reminder_bytes_ui32; i++)
        {
            *(uint8_t *)l_dst_pui64 = *(uint8_t *)l_src_pui64;
            l_dst_pui64 = (uint64_t*)((uint8_t *)l_dst_pui64 + 1);
            l_src_pui64 = (uint64_t*)((uint8_t *)l_src_pui64 + 1);
        }
    }
    return;
}