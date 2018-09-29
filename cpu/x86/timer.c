#include "timer.h"
#include "isr.h"
#include "ports.h"
#include "screen.h"
#include "cpu/type.h"
#include "libc/utils.h"

uint32_t g_TickCounter = 0;

static void timer_callback(registers_t *regs) {
    g_TickCounter++;
    UNUSED(regs);
}

void init_pit_timer(uint16_t freq)
{
    if(freq == 0) {
	    kprint("Error: Invalid timer freq 0\n");
	    ASSERT(0);
    }

   // Register interrupt handler
   register_interrupt_handler(IRQ0, timer_callback);
   
    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t mode = PIT_TIMER_BINARY_MODE | PIT_TIMER_SQUARE_WAVE \
		   | PIT_TIMER_LO_HI | PIT_TIMER_SEL_CHANNEL_0;
    /* Send the command */
    port_outb(PIT_TIMER_COMMAND_PORT, mode); /* Command port */
    port_outb(PIT_TIMER_CHANNEL_0_PORT, LOW_BYTE(divisor));
    port_outb(PIT_TIMER_CHANNEL_0_PORT, HIGH_BYTE(divisor));
}

