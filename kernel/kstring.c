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

void ReverseStr(char* str, size_t len){
	for (size_t i = 0; i < len/2; i++) {
		char first = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = first;
	}
}

static const char AlphaNum[] = "0123456789abcdefghijklmnopqrstuvwxyz";

void int2str(intmax_t num, unsigned base, char* str){
	if (base > 36) {
		terminal_writestring("Warning: int2str can accept base in range 0-36!"); //TODO make an error/warning handling
		return;
	}
	bool isNegative = false;

	int curDigit = 0;
	if (num < 0) {
		isNegative = true;
		num *= -1;
	}

	while (num > base){
		int digit = num % base;
		num /= base;
		str[curDigit] = AlphaNum[digit];
		curDigit++;
	}

	int digit = num % base;
	num /= base;
	str[curDigit] = AlphaNum[digit];
	curDigit++;

	if(isNegative){
		str[curDigit] = '-';
		curDigit++;
	}
	str[curDigit+1] = '\0';
	ReverseStr(str, strlen(str));
}

void uint2str(uintmax_t num, unsigned base, char* str){
	if (base > 36) {
		terminal_writestring("Warning: uint2str can accept base in range 0-36!"); //TODO make an error/warning handling
		return;
	}

	int curDigit = 0;

	while (num > base){
		int digit = num % base;
		num /= base;
		str[curDigit] = AlphaNum[digit];
		curDigit++;
	}
	int digit = num % base;
	num /= base;
	str[curDigit] = AlphaNum[digit];
	curDigit++;
	str[curDigit+1] = '\0';
	ReverseStr(str, strlen(str));

}
