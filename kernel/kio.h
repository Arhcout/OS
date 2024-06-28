#ifndef KIO_H
#define KIO_H
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#if defined (__i386__)

static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
    /* There's an outb %al, $imm8 encoding, for compile-time constant port numbers that fit in 8b. (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline void io_wait()
{
    outb(0x80, 0);
}

#else
#error Current target unimplemented
#endif

void kprint(const char* str);
void kprintf(const char* fmt, ...);
void kvprintf(const char* fmt, char* dest, size_t n, va_list list);

#endif // KIO_H
