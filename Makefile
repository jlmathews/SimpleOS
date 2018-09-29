C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c cpu/x86/*.c libc/*.c)
HEADERS = $(wildcard . kernel drivers cpu cpu/x86 libc)
INC=$(foreach d, $(HEADERS), -I$d)
OBJ = ${C_SOURCES:.c=.o cpu/x86/interrupt.o} 

CC = /usr/local/customi386elfgcc/bin/i386-elf-gcc
GDB = /usr/local/customi386elfgcc/bin/i386-elf-gdb

CFLAGS = -g -ffreestanding -Wall -Wextra -Werror -fno-exceptions -m32 $(INC)

os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

# Create symbol file
kernel.lst: kernel.elf
	i386-elf-objdump -d $< > $@

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -S -fda os-image.bin -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o *.elf *.lst
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o cpu/x86/*.o libc/*.o
