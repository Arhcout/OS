#include "Interrupts.h"
#include "Serial.h"
#include "arch/i686-elf/GDT.h"
#include "arch/i686-elf/Paging.h"
#include "kio.h"
#include "tty.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern uint32_t kernelEnd;

void kernel_main(void) {
  terminal_initialize();
  InitGDT();
  InitInterrupt();
  kSprintf(COM1, "kernelEnd: 0x%x\n", &kernelEnd);
  InitPaging();

  InitDebugSerial(COM1);

  kprintf("%llx\n", 0xdeadbeef12345678);

  for (;;) {
    UpdateSerial(COM1);
  }
}
