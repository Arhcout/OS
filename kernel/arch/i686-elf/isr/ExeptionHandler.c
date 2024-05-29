#include "../isr.h"
#include "../../../kio.h"
#include <stdint.h>

static void _PrintFrame(InterrupFrame* frame){
	kprintf("Frame info:\n\
	IP: 0x%x\n\
	CS: 0x%x\n\
	rflags: %x\n\
	reg sp: 0x%x\n\
	Stack seg: 0x%x\n",
	frame->IP, frame->CS, frame->rflags, frame->registerStackPointer, frame->stackSegment);
}

__attribute__((interrupt))
void ExeptionHandler(InterrupFrame* frame) {
	kprintf("Exeption i.e go implement the isr you lazy fuck.\n");
	_PrintFrame(frame);
	kprintf("And now its gonna halt. Bye and good luck!\n"); 
	__asm__ volatile ("cli; hlt"); // Completely hangs the computer
	__builtin_unreachable();
}

__attribute__((interrupt))
void DivideByZeroExeptionHandler(InterrupFrame* frame){
	kprintf("Divide by zero exeption!\n");
	_PrintFrame(frame);
	__asm__ volatile ("cli; hlt"); // Completely hangs the computer
	__builtin_unreachable();
}
