#include "isr.h"
#include "kio.h"
#include <stdint.h>

#define _PrintFrame(frame)                                                     \
  kprintf("Frame info:\n\
	IP: 0x%x\n\
	CS: 0x%x\n\
	rflags: %x\n\
	reg sp: 0x%x\n\
	Stack seg: 0x%x\n",                                                    \
          frame->IP, frame->CS, frame->rflags, frame->registerStackPointer,    \
          frame->stackSegment);                                                \
  register uint32_t eax asm("eax"), ebx asm("ebx"), ecx asm("ecx"),            \
      edx asm("edx"), esp asm("esp"), ebp asm("ebp"), edi asm("edi"),          \
      esi asm("esi");                                                          \
  kprintf("Registers:\n\
	eax: %x\n\
	ebx: %x\n\
	ecx: %x\n\
	edx: %x\n\
	esp: %x\n\
	ebp: %x\n\
	edi: %x\n\
	esi: %x\n\
	",                                                                     \
          eax, ebx, ecx, edx, esp, ebp, edi, esi);

static void _PrintSelectorError(uint32_t err) {
  kprintf("%s ", (err & 0x1) == 1 ? "External" : "Internal");
  switch ((err >> 1) & 0x3) {
  case 0:
    kprintf("GDT ");
    break;
  case 3:
  case 1:
    kprintf("IDT ");
    break;
  case 2:
    kprintf("LDT ");
    break;
  }
  kprintf("index %x\n", err >> 3 & 0x1FFF);
}

__attribute__((interrupt)) void ExeptionHandler(InterrupFrame *frame) {
  kprintf("Exeption i.e go implement the isr you lazy fuck.\n");
  _PrintFrame(frame);
  kprintf("And now its gonna halt. Bye and good luck!\n");
  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void
DivideByZeroExeptionHandler(InterrupFrame *frame) {
  kprintf("Divide by zero exeption!\n");
  _PrintFrame(frame);
  kprintf("And now its gonna halt. Bye and good luck!\n");
  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void NMIHandler(InterrupFrame *frame) {
  kprintf("NMI interrupt RAM error? thats weird\n\n");
  _PrintFrame(frame);
  kprintf("And now its gonna halt. Bye and good luck!\n");
  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void OverflowHandler(InterrupFrame *frame) {
  kprintf("Overflow exeption\n\n");
  _PrintFrame(frame);
  kprintf("And now its gonna halt. Bye and good luck!\n");
  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void BoundRangeExeededHandler(InterrupFrame *frame) {
  kprintf("Bound range exeeded exeption\n\n");
  _PrintFrame(frame);
  kprintf("And now its gonna halt. Bye and good luck!\n");
  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void InvalidOpcodeHandler(InterrupFrame *frame) {
  kprintf("Invalide opcode exeption\n\n");
  _PrintFrame(frame);
  kprintf("And now its gonna halt. Bye and good luck!\n");
  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void
DeviceNotAvailableHandler(InterrupFrame *frame) {
  kprintf("Device Not Available exeption\n\n");
  _PrintFrame(frame);
  kprintf("And now its gonna halt. Bye and good luck!\n");
  __asm__ volatile(
      "cli; hlt"); // Completely hangs the comControlProtectionFaultputer
  __builtin_unreachable();
}

__attribute__((interrupt)) void DoubleFaultHandler(InterrupFrame *frame,
                                                   uint32_t err) {
  kprintf("Double fault exeption. err code (always zero?) %x\n\n", err);
  _PrintFrame(frame);
  kprintf("And now its gonna halt. Bye and good luck!\n");
  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void InvalidTSSHandler(InterrupFrame *frame,
                                                  uint32_t err) {
  kprintf("Invalid TSS exeption!\n\n");
  _PrintFrame(frame);
  _PrintSelectorError(err);
  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void SegmentNotPresentHandler(InterrupFrame *frame,
                                                         uint32_t err) {
  kprintf("Segment not present exeption\n\n");
  _PrintFrame(frame);
  _PrintSelectorError(err);
  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void StackSegmentFaultHandler(InterrupFrame *frame,
                                                         uint32_t err) {
  kprintf("Stack segment fault exeption\n\n");
  _PrintFrame(frame);
  _PrintSelectorError(err);
  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void
GeneralProtectionFaultHandler(InterrupFrame *frame, uint32_t err) {
  kprintf("General protection fault exeption\n\n");
  _PrintFrame(frame);
  _PrintSelectorError(err);
  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void PageFaultHandler(InterrupFrame *frame,
                                                 uint32_t err) {
  kprintf("General protection fault exeption\n\n");
  _PrintFrame(frame);

  kprintf("err code: %b", err);

  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void
x87FloatingPointExceptionHandler(InterrupFrame *frame) {
  kprintf("x87 Floating-Point exeption\n\n");
  _PrintFrame(frame);

  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void AlignmentCheckHandler(InterrupFrame *frame) {
  kprintf("Alignment check exeption\n\n");
  _PrintFrame(frame);

  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void MachinCheckHandler(InterrupFrame *frame) {
  kprintf("Machin check exeption\n\n");
  _PrintFrame(frame);

  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void
SIMDFloatingPointExceptionHandler(InterrupFrame *frame) {
  kprintf("SIMD Floating Point exeption\n\n");
  _PrintFrame(frame);

  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void
VirtualizationExceptionHandler(InterrupFrame *frame) {
  kprintf("Virtualization exeption\n\n");
  _PrintFrame(frame);

  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void
ControlProtectionFaultHandler(InterrupFrame *frame, uint32_t err) {
  kprintf("Control protection fault exeption\n\n");
  _PrintFrame(frame);
  _PrintSelectorError(err);
  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void
HypervisorInjectionExeptionHandler(InterrupFrame *frame) {
  kprintf("Hypervisor Injection exeption\n\n");
  _PrintFrame(frame);
  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void
VMMCommunicationExeptionHandler(InterrupFrame *frame, uint32_t err) {
  kprintf("VMM Communication exeption\n\n");
  _PrintFrame(frame);
  kprintf("Error code: %x\n", err);
  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}

__attribute__((interrupt)) void SecurityExeptionHandler(InterrupFrame *frame,
                                                        uint32_t err) {
  kprintf("Security exeption\n\n");
  _PrintFrame(frame);
  kprintf("Error code: %x\n", err);
  kprintf("And now its gonna halt. Bye and good luck!\n");

  __asm__ volatile("cli; hlt"); // Completely hangs the computer
  __builtin_unreachable();
}
