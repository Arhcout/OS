#include "PIC.h"
#include "Serial.h"
#include "isr.h"
#include "kio.h"

__attribute__((interrupt)) void Serial2Handler(InterrupFrame *frame) {
  (void)frame;
  QueueRead(COM2);
  PICSendEOI(3);
}

__attribute__((interrupt)) void Serial1Handler(InterrupFrame *frame) {
  (void)frame;
  QueueRead(COM1);
  PICSendEOI(4);
}
