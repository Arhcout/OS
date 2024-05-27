#include "kio.h"
#include "kstring.h"
#include "tty.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

void kprint(const char* str){
	
}



void kprintf(const char* fmt, ...){
	va_list list;
	va_start(list, fmt);

	while (*fmt){
		if(*fmt == '%'){
			fmt++;

			switch (*fmt){
				case '%':
					terminal_putchar('%');
					break;
				case 's':
				{
					char* str;
					str = va_arg(list, char*);
					terminal_writestring(str);
					break;
				}
				case 'i':
				case 'd':
				{
						int num = va_arg(list, int);

						char strNum[11];
						int2str(num, 10, strNum);
						terminal_writestring(strNum);
						break;
				}
				case 'x':
				{
					unsigned num = va_arg(list, unsigned);

					char strNum[9];
					uint2str(num, 16, strNum);
					terminal_writestring(strNum);
					break;
				}
				case 'c':
				{
					char c = va_arg(list, int);
					terminal_putchar(c);
					break;
				}
			}
			fmt++;
		}
		else {
			terminal_putchar(*fmt);
			fmt++;
		}
	}

	va_end(list);
}
