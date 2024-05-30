#ifndef SERIAL_H
#define SERIAL_H
#include <stdint.h>

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

void QueueRead(uint32_t port);
void UpdateSerial(uint32_t port);
char ReadSerial(uint32_t port);
void WriteSerial(uint32_t port, char a);
int InitDebugSerial(uint32_t port);

#endif // SERIAL_H
