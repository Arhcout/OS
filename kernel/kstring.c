#include "kstring.h"
#include "tty.h"
#include <stdbool.h>
#include <stdint.h>

size_t strlen(const char *s){
	size_t len = 0;
	while (*s){
		len++;
		s++;
	}
	return len;
}

void strcpy(const char* src, char* dest){
	for (size_t i = 0; i < strlen(src);	i++) {
		dest[i] = src[i];
	}
}

void strncpy(const char* src, char* dest, int n){
	for (int i = 0; i < n;	i++) {
		dest[i] = src[i];
	}
}

void* memset(void* ptr, int v, size_t n){
	while (n--) {
		((char*)ptr)[n] = v;
	}
	return ptr;
}

void* memcpy(void* dest, const void* src, size_t n){
	for (size_t i = 0; i < n/sizeof(uint32_t); i++) {
		((uint32_t*)dest)[i] = ((uint32_t*)src)[i];
	}
	for (size_t i = n - n%sizeof(uint32_t); i < n; i++) {
		((uint8_t*)dest)[i] = ((uint8_t*)src)[i];
	}
	return dest;
}

void ReverseStr(char* str, size_t len){
	for (size_t i = 0; i < len/2; i++) {
		char first = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = first;
	}
}

static const char AlphaNum[] = "0123456789abcdefghijklmnopqrstuvwxyz";

bool IsDigit(unsigned char c){
	return c - 0x30 < 10;
}

const char* str2int(const char* str, int* out){
	const char* cur = str;
	int digit;
	int i = 1;
	while (IsDigit(*cur)) {
		digit = *cur - 0x30;
		*out += digit * i;
		i *= 10;
		cur++;
	}
	return cur;
}

void int2str(intmax_t num, unsigned base, char* str){
	if (base > 36) {
		terminal_writestring("Warning: int2str can accept base in range 0-36!"); //TODO make an error/warning handling
		return;
	}
	bool isNegative = false;
	
	if(num == 0){
		strcpy("0", str);
		return;
	}
	if (num < 0) {
		isNegative = true;
	}

	int curDigit = 0;

	while (num > 0){
		int digit = num % base;
		num /= base;
		str[curDigit] = AlphaNum[digit];
		curDigit++;
	}

	if(isNegative){
		str[curDigit] = '-';
		curDigit++;
	}
	str[curDigit+1] = '\0';
	ReverseStr(str, strlen(str));
}

void uint2str(uintmax_t num, unsigned base, char* str){
	if (base > 36) {
		terminal_writestring("Warning: int2str can accept base in range 0-36!"); //TODO make an error/warning handling
		return;
	}
	
	if(num == 0){
		strcpy("0", str);
		return;
	}

	int curDigit = 0;

	while (num > 0){
		int digit = num % base;
		num /= base;
		str[curDigit] = AlphaNum[digit];
		curDigit++;
	}

	str[curDigit+1] = '\0';
	ReverseStr(str, strlen(str));
}
