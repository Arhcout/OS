#include "GDT.h"
#include "../../kio.h"
#include <stdint.h>

static uint64_t GDT[6];

static uint8_t TSS[0x68];

extern void setGdt(uint16_t limit, uint32_t base);
extern void reloadSegments();

void CreateTSS(){

	uint32_t base = (uint32_t)TSS;
	uint32_t limit = sizeof(TSS)-1;
	uint16_t flag = 0x89;
	// Create the high 32 bit segment
	GDT[5]  =  limit       & 0x000F0000;         // set limit bits 19:16
	GDT[5] |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
	GDT[5] |= (base >> 16) & 0x000000FF;         // set base bits 23:16
	GDT[5] |=  base        & 0xFF000000;         // set base bits 31:24
 
	// Shift by 32 to allow for low part of segment
	GDT[5] <<= 32;

	// Create the low 32 bit segment
	GDT[5] |= base  << 16;                       // set base bits 15:0
	GDT[5] |= limit  & 0x0000FFFF;               // set limit bits 15:0

	kprintf("TSS: %x", GDT[5]);
}


void InitGDT(){
	__asm__("cli");
	// Null descriptor
	GDT[0] = 0;
	// Kernel code segment
	GDT[1] = 0x00CF9A000000FFFF;
	// kernel data segment
	GDT[2] = 0x00CF92000000FFFF;
	// user code segment
	GDT[3] = 0x00CFFA000000FFFF;
	// user data segment
	GDT[4] = 0x00CFF2000000FFFF;
	// TTS
	CreateTSS();

	setGdt(sizeof(GDT) - 1, (uint32_t)GDT);

	reloadSegments();
}
