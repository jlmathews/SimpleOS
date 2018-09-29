#ifndef SIMPLEOS_PORTS_H
#define SIMPLEOS_PORTS_H

#include <stdint.h>

#define PS2_IO_PORT_DATA	0x60
#define PS2_IO_PORT_CMD_STS	0x64

#define PS2_OUTPUT_BUFFER_STS	(0x1)

unsigned char port_inb (uint16_t port);
void port_outb (uint16_t port, uint8_t data);
unsigned short port_inw (uint16_t port);
void port_outw (uint16_t port, uint16_t data);

#endif
