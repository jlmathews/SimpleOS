#include "keyboard.h"
#include "cpu/x86/isr.h"
#include "cpu/x86/ports.h"
#include "screen.h"
#include "libc/string.h"
#include "libc/utils.h"
#include "drivers/shell.h"

#include <stdint.h>

typedef enum {
	ERROR=0x0,
	ESCAPE=0x1,
	BACKSPACE=0xE,
	ENTER=0x1C,
	SCANCODE_MAX=57,
} KeyScanCode_t;

static char key_buffer[256];

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static KeyScanCode_t read_keyboard_scancode()
{
	// Read keyboard scancode from port
	return (KeyScanCode_t)port_inb(PS2_IO_PORT_DATA);
}

static uint8_t is_buffer_full()
{
	return port_inb(PS2_IO_PORT_CMD_STS) & PS2_OUTPUT_BUFFER_STS;
}

static void _process_keyboard()
{
    KeyScanCode_t scancode = read_keyboard_scancode();
    
    if (scancode > SCANCODE_MAX)
	    return;
    if (scancode == BACKSPACE) {
        rstrip(key_buffer, 1);
        kprint_backspace();
    } else if (scancode == ESCAPE) {
	kprint("\nESC\n\0");
        key_buffer[0] = '\0';
    } else if (scancode == ENTER) {
        kprint("\n");
        process_user_input(key_buffer);
        key_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int)scancode];
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
}

void process_keyboard()
{
	if(is_buffer_full()) {
		_process_keyboard();
	}
}

static void keyboard_callback(registers_t *regs) {
    UNUSED(regs);
    _process_keyboard();
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
