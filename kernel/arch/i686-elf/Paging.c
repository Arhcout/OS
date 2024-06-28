#include "Paging.h"
#include "../../kio.h"
#include <stdint.h>

#define BOOTSTRAP_PAGEDIR_NUM 1

__attribute__((__aligned__(0x1000)))
uint32_t bootStrapPageDir[BOOTSTRAP_PAGEDIR_NUM];

__attribute__((__aligned__(0x1000)))
uint32_t bootStrapPageTable[BOOTSTRAP_PAGEDIR_NUM][1024];

void MapPhysicalPage(uint32_t ppage, uint32_t vpage, uint8_t flags, uint32_t* pd, uint32_t** pts){
	uint32_t pdEntry = vpage != 0 ? vpage / 0xFF400000      : 0;
	uint32_t ptEntry = vpage != 0 ? (vpage / 0x1000) % 1024 : 0;

	if((pd[pdEntry] & 1) == 0){
		pd[pdEntry] = ((uint32_t)pts[pdEntry] & 0xFFFFF000) | flags;
	}

	pts[pdEntry][ptEntry] = (ppage & 0xFFFFF000) | flags;
}

void InitPaging(){
	bootStrapPageDir[0] = ((uint32_t)bootStrapPageTable & 0xFFFFF000) | 0x03; // PS=0; A=0; PCD=0; PWT=0; U/S=0; R/W=1; P=1
	
	// Identity mapping first meg
	for (uint32_t i = 0; i < 0x100000; i += 0x1000) {
		MapPhysicalPage(i, i, 0x03, bootStrapPageDir, (uint32_t**)bootStrapPageTable);
	}

	asm("mov %0, %%eax;\
 mov %%eax, %%cr3;\
 mov %%cr0, %%eax;\
 or 0x80000001, %%eax;\
 mov %%eax, cr0;" : :"r" (bootStrapPageDir));
}
