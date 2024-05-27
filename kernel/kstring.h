#ifndef KSTRING_H
#define KSTRING_H

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *s);
void ReverseStr(char* str, size_t len);
void int2str(intmax_t numn, unsigned base, char* str);
void uint2str(uintmax_t num, unsigned base, char* str);

#endif // KSTRING_H
