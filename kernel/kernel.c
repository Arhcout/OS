#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "Interrupts.h"
#include "arch/i686-elf/GDT.h"
#include "tty.h"
#include "kio.h"

void kernel_main(void) 
{
	terminal_initialize();
	kprintf("Hello world!\n");

	InitGDT();
	InitInterrupt();

	for(;;) __asm__("hlt");
}
