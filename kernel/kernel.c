#include "Interrupts.h"
#include "Serial.h"
#include "kio.h"
#include "tty.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern uint32_t kernelEnd;

void kernel_main(void) {
  terminal_initialize();
  InitInterrupt();
  InitDebugSerial(COM1);

  kSprintf(COM1, "kernel size (in bytes): 0x%x\r\n", (&kernelEnd) - 0x100000);

  for (;;) {
    UpdateSerial(COM1);
  }
}
