#include "../isr.h"
#include "../PIC.h"
#include "../../../kio.h"

__attribute__((interrupt))
void KeyboardIntHandler(InterrupFrame* frame){
	(void)frame;
	unsigned char scan_code = inb(0x60);
	kprintf("Keyboard int! scan code: %x\n", scan_code);
	PICSendEOI(1);
}
