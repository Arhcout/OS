#ifndef ISR_H
#define ISR_H

#include <stdint.h>

typedef struct{
	uint32_t IP;
	uint32_t CS;
	uint32_t rflags;
	uint32_t registerStackPointer;
	uint32_t stackSegment;
} InterrupFrame;

__attribute__((interrupt)) void ExeptionHandler(InterrupFrame* frame);
__attribute__((interrupt)) void DivideByZeroExeptionHandler(InterrupFrame* frame);
__attribute__((interrupt)) void KeyboardIntHandler(InterrupFrame* frame);
#endif // ISR_H
