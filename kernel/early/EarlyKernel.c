#include "Defines.h"
#include "GDT.h"
#include <stdint.h>

uint32_t E_HighKernelPaging();

SECTION(.boot_text)
uint32_t EarlyKernel() {
  InitGDT();
  return E_HighKernelPaging();
}
