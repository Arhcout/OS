#include "Paging.h"
#include "../../Serial.h"
#include "../../kio.h"
#include <stdint.h>

#define BOOTSTRAP_PAGEDIR_NUM 2

__attribute__((
    __aligned__(0x1000))) uint32_t bootStrapPageDir[BOOTSTRAP_PAGEDIR_NUM];

__attribute__((__aligned__(
    0x1000))) uint32_t bootStrapPageTable[BOOTSTRAP_PAGEDIR_NUM][1024];

void MapPhysicalPage(uint32_t ppage, uint32_t vpage, uint8_t pageTableFlags,
                     uint8_t pageDirFlags, uint32_t *pd, uint32_t **pts) {
  uint32_t pdEntry = vpage >> 22;
  uint32_t ptEntry = vpage >> 12 & 0x03FF;

  kSprintf(COM1, "\
pdEntry:\t0x%x\r\n\
ptEntry:\t0x%x\r\n\
vpage:  \t0x%x\r\n\
ppage:  \t0x%x\r\n",
           pdEntry, ptEntry, vpage, ppage);

  // if target page table isn't present
  if ((pd[pdEntry] & 1) == 0) {
    pd[pdEntry] = ((uint32_t)(&pts[pdEntry]) & 0xFFFFF000) | pageDirFlags;
  }
  uint32_t *pageTables = (uint32_t *)(pd[pdEntry] & 0xFFFFF000);

  pageTables[ptEntry] = (ppage & 0xFFFFF000) | pageTableFlags;
  kSprintf(COM1, "pts:    \t0x%x\r\n\r\n", pageTables[ptEntry]);
}

extern uint32_t kernelEnd;

// From Paging.s
extern void EnablePaging(void *pd);

void InitPaging() {
  bootStrapPageDir[0] = ((uint32_t)(&bootStrapPageTable[0]) & 0xFFFFF000) |
                        0x03; // PS=0; A=0; PCD=0; PWT=0; U/S=0; R/W=1; P=1

  // Identity mapping first meg
  for (uint32_t i = 0; i < 0x100000; i += 0x1000) {
    MapPhysicalPage(i, i, 0x03, 0x03, bootStrapPageDir,
                    (uint32_t **)bootStrapPageTable);
  }

  for (uint32_t i = 0x100000; i < (uint32_t)&kernelEnd; i += 0x1000) {
    MapPhysicalPage(i, i, 0x03, 0x03, bootStrapPageDir,
                    (uint32_t **)bootStrapPageTable);
  }

  EnablePaging(bootStrapPageDir);
}
