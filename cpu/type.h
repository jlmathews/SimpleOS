#ifndef SIMPLEOS_TYPE_H
#define SIMPLEOS_TYPE_H

#include <stdint.h>

#define LOW_BYTE(address) (uint8_t)((address) & 0xFF)
#define HIGH_BYTE(address) (uint8_t)(((address) >> 8) & 0xFF)

#define LOW_WORD(address) (uint16_t)((address) & 0xFFFF)
#define HIGH_WORD(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#endif
