#ifndef __ALLOC__H__
#define __ALLOC__H__


#include <stdint.h>
#include <stddef.h>


void *kmalloc(uint32_t f_size_ui32);
void kmemncpy(void *f_src_pvd, void *f_dst_pvd, uint32_t f_size_ui32);

#define MiB (1<<20)

#endif