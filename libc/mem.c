#include "mem.h"

static Memory_t g_heap;

// Initialize memory structures
void so_meminit()
{
	g_heap.base_addr = 0x10000;
	g_heap.size = 0x10000;
	g_heap.top_addr = 0x10000;
}

void so_memcpy(uint8_t *dest, uint8_t *src, uint32_t size)
{
    uint32_t i;
    for (i = 0; i < size; i++) {
        *(dest + i) = *(src + i);
    }
}

void so_memset(uint8_t *ptr, uint8_t pattern, uint32_t size)
{
    uint8_t *temp = (uint8_t *)ptr;
    for ( ; size != 0; size--)
	    *temp++ = pattern;
}

void *so_malloc(size_t size)
{
	void *addr = NULL;
	uint32_t remaining_bytes = g_heap.size - \
				   (g_heap.top_addr - g_heap.base_addr);
	if(size == 0) {
		return NULL;
	}

	if(size > remaining_bytes) {
		return NULL;
	}

	addr = (void*)g_heap.top_addr;
	g_heap.top_addr += size;

	return addr;
}

