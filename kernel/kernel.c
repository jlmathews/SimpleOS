#include "cpu/x86/isr.h"
#include "cpu/x86/timer.h"
#include "drivers/keyboard.h"
#include "drivers/screen.h"
#include "kernel.h"
#include "libc/string.h"
#include "libc/mem.h"
#include <stdint.h>

static void main_loop();

static uint8_t *addr;

void kernel_main() {
    meminit();
    isr_install();
    irq_install();
    asm volatile("int $03");
    addr = malloc(100);
    if(addr != NULL)
    	*addr = 0xab;
    main_loop();
}

static void main_loop()
{
    while(1) {
	//process_keyboard();
    }
}

