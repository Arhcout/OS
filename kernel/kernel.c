#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "Interrupts.h"
#include "Serial.h"
#include "arch/i686-elf/GDT.h"
#include "tty.h"
#include "kio.h"

void kernel_main(void) 
{
	InitGDT();
	InitInterrupt();

	InitDebugSerial(COM1);

	terminal_initialize();
	kprintf("Hello world!\n");

	for(;;) {
		UpdateSerial(COM1);
	}
}
