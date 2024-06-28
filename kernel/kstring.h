#ifndef KSTRING_H
#define KSTRING_H

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *s);
void ReverseStr(char* str, size_t len);
const char* str2int(const char* str, int* out);
void int2str(intmax_t numn, unsigned base, char* str);
void uint2str(uintmax_t num, unsigned base, char* str);
void strcpy(const char* src, char* dest);
void strncpy(const char* src, char* dest, int n);
void* memset(void* ptr, int v, size_t n);
void* memcpy(void* dest, const void* src, size_t n);

#endif // KSTRING_H
