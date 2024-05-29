#include "../../Interrupts.h"
#include "GDT.h"
#include "ArchUtils.h"
#include "isr.h"
#include "PIC.h"
#include <stdint.h>

typedef struct {
	uint16_t    isrLow;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isrHigh;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) IDTEntry;

__attribute__((aligned(0x10))) 
static IDTEntry idt[256]; // Create an array of IDT entries; aligned for performance

static void IDTSetDescriptor(uint8_t vector, void* isr, uint8_t flags) {
    IDTEntry* descriptor = &idt[vector];
 
    descriptor->isrLow = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs = GDT_K_CODE_OFF;
    descriptor->attributes = flags;
    descriptor->isrHigh = (uint32_t)isr >> 16;
    descriptor->reserved = 0;
}

void* isrs[] = {
	DivideByZeroExeptionHandler, // Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	ExeptionHandler, //TODO: Implement it! Protected Mode Exceptions (Reserved by Intel) 
	
	ExeptionHandler, //TODO: implement it
	KeyboardIntHandler, // KB Interrupt handler
	0              , // for internal use of PIC only
	ExeptionHandler, //TODO: implement it
	ExeptionHandler, //TODO: implement it
	ExeptionHandler, //TODO: implement it
	ExeptionHandler, //TODO: implement it
	ExeptionHandler, //TODO: implement it
	ExeptionHandler, //TODO: implement it
	ExeptionHandler, //TODO: implement it
	ExeptionHandler, //TODO: implement it
	ExeptionHandler, //TODO: implement it
	ExeptionHandler, //TODO: implement it
	ExeptionHandler, //TODO: implement it
	ExeptionHandler, //TODO: implement it
};

// from Interrupts.s
extern void setIdt(uint16_t limit, uint32_t base);

void InitInterrupt(){
	RemapPIC(0x20, 0x27);
	DisablePIC(); // Mask all IRQ lines
	ClearIRQMask(1); // Enable keyboard inturrupt
	uint8_t vector = 0;
	for (; vector < 32; vector++) {
		// flags: Trap gate, DPL 0, Present
		IDTSetDescriptor(vector, isrs[vector], 0b10001111);
	}
	for (; vector < 32+16; vector++) {
		// flags: Interrupt gate, DPL 0, Present
		IDTSetDescriptor(vector, isrs[vector], 0b10001110);
	}
	setIdt(sizeof(idt)-1, (uintptr_t)&idt[0]);
	reloadSegments();
	__asm__ volatile ("sti");
}
