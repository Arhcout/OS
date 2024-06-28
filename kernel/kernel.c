#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "Interrupts.h"
#include "Serial.h"
#include "arch/i686-elf/GDT.h"
#include "arch/i686-elf/Paging.h"
#include "tty.h"
#include "kio.h"

void kernel_main(void) 
{
	terminal_initialize();
	InitGDT();
	InitInterrupt();
	InitPaging();

	InitDebugSerial(COM1);

	kprintf("%llx\n", 0xdeadbeef12345678);

	WriteStringToSerial(COM1, "Hello serial!\n");

	for(;;) {
		UpdateSerial(COM1);
	}
}
