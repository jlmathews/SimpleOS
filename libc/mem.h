#ifndef SIMPLEOS_MEM_H
#define SIMPLEOS_MEM_H

#include <stdint.h>
#include <stddef.h>

typedef struct
{
	uint32_t base_addr;
	uint32_t size;
	uint32_t top_addr;
} Memory_t;

void so_meminit();
void so_memcpy(uint8_t *dest, uint8_t *src, uint32_t size);
void so_memset(uint8_t *dest, uint8_t val, uint32_t len);
void *so_malloc(size_t size);

#define meminit() so_meminit()
#define memcpy(dest, src, size) so_memcpy(dest, src, size)
#define memset(ptr, pattern, size) so_memset(ptr, pattern, size)
#define malloc(size) so_malloc(size)

#endif
