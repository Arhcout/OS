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
__attribute__((interrupt)) void NMIHandler(InterrupFrame* frame);
__attribute__((interrupt)) void OverflowHandler(InterrupFrame* frame);
__attribute__((interrupt)) void BoundRangeExeededHandler(InterrupFrame* frame);
__attribute__((interrupt)) void InvalidOpcodeHandler(InterrupFrame* frame) ;
__attribute__((interrupt)) void DeviceNotAvailableHandler(InterrupFrame* frame);
__attribute__((interrupt)) void DoubleFaultHandler(InterrupFrame* frame, uint32_t err);
__attribute__((interrupt)) void InvalidTSSHandler(InterrupFrame* frame, uint32_t err);
__attribute__((interrupt)) void SegmentNotPresentHandler(InterrupFrame* frame, uint32_t err);
__attribute__((interrupt)) void StackSegmentFaultHandler(InterrupFrame* frame, uint32_t err);
__attribute__((interrupt)) void GeneralProtectionFaultHandler(InterrupFrame* frame, uint32_t err);
__attribute__((interrupt)) void PageFaultHandler(InterrupFrame* frame, uint32_t err);
__attribute__((interrupt)) void x87FloatingPointExceptionHandler(InterrupFrame* frame);
__attribute__((interrupt)) void AlignmentCheckHandler(InterrupFrame* frame);
__attribute__((interrupt)) void MachinCheckHandler(InterrupFrame* frame);
__attribute__((interrupt)) void SIMDFloatingPointExceptionHandler(InterrupFrame* frame);
__attribute__((interrupt)) void VirtualizationExceptionHandler(InterrupFrame* frame);
__attribute__((interrupt)) void ControlProtectionFaultHandler(InterrupFrame* frame, uint32_t err);
__attribute__((interrupt)) void HypervisorInjectionExeptionHandler(InterrupFrame* frame);
__attribute__((interrupt)) void VMMCommunicationExeptionHandler(InterrupFrame* frame, uint32_t err);
__attribute__((interrupt)) void SecurityExeptionHandler(InterrupFrame* frame, uint32_t err);
__attribute__((interrupt)) void KeyboardIntHandler(InterrupFrame* frame);
__attribute__((interrupt)) void Serial2Handler(InterrupFrame* frame);
__attribute__((interrupt)) void Serial1Handler(InterrupFrame* frame);
#endif // ISR_H
