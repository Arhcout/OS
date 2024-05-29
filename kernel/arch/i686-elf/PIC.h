#ifndef PIC_H
#define PIC_H

#include <stdint.h>

void DisablePIC();
void PICSendEOI(uint8_t irq);
void RemapPIC(int offset1, int offset2);

void SetIRQMask(uint8_t IRQline);
void ClearIRQMask(uint8_t IRQline);

#endif
