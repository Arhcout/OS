#ifndef TTY_H
#define TTY_H
#include <stdint.h>
#include <stddef.h>

void terminal_initialize();
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_scrol();
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

#endif // TTY_H
