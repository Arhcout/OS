#include "Paging.h"
#include <stdint.h>

#define BOOTSTRAP_PAGEDIR_NUM 1024

__attribute__((
    __aligned__(0x1000))) uint32_t kernelPageDir[BOOTSTRAP_PAGEDIR_NUM];

__attribute__((
    __aligned__(0x1000))) uint32_t kernelPageTable[BOOTSTRAP_PAGEDIR_NUM][1024];

void MapPhysicalPage(uint32_t ppage, uint32_t vpage, uint8_t pageTableFlags,
                     uint8_t pageDirFlags, uint32_t *pd, uint32_t **pts) {
  uint32_t pdEntry = vpage >> 22;
  uint32_t ptEntry = vpage >> 12 & 0x03FF;

  // if target page table isn't present
  if ((pd[pdEntry] & 1) == 0) {
    pd[pdEntry] = ((uint32_t)(&pts[pdEntry]) & 0xFFFFF000) | pageDirFlags;
  }
  uint32_t *pageTables = (uint32_t *)(pd[pdEntry] & 0xFFFFF000);

  pageTables[ptEntry] = (ppage & 0xFFFFF000) | pageTableFlags;
}

extern uint32_t kernelEnd;

// From Paging.s
extern void EnablePaging(void *pd);

void HighKernelPaging() {
  kernelPageDir[0] = ((uint32_t)(&kernelPageTable[0]) & 0xFFFFF000) |
                     0x03; // PS=0; A=0; PCD=0; PWT=0; U/S=0; R/W=1; P=1

  for (uint32_t i = 0; i < (uint32_t)&kernelEnd; i += 0x1000) {
    // Identity mapping first meg
    MapPhysicalPage(i, i, 0x03, 0x03, kernelPageDir,
                    (uint32_t **)kernelPageTable);

    // map the kernel + first meg to higher half (0xC0000000)
    MapPhysicalPage(i, i + 0xC0000000, 0x03, 0x03, kernelPageDir,
                    (uint32_t **)kernelPageTable);
  }
}
