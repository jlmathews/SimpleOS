#ifndef SIMPLEOS_PIT_TIMER_H
#define SIMPLEOS_PIT_TIMER_H

#include <stdint.h>

#define PIT_TIMER_CHANNEL_0_PORT	(0x40)
#define PIT_TIMER_COMMAND_PORT		(0x43)

#define PIT_TIMER_BINARY_MODE		(0x0)
// Operating Mode
#define PIT_TIMER_SQUARE_WAVE		(0x3 << 1)
// Access Mode
#define PIT_TIMER_LO_HI			(0x3 << 4)
// Select Channel
#define PIT_TIMER_SEL_CHANNEL_0		(0x0 << 6)

extern uint32_t g_TickCounter;

void init_pit_timer(uint16_t freq);

#endif
