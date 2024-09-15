#include "kio.h"
#include "Serial.h"
#include "kstring.h"
#include "tty.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

void kprint(const char *str) { terminal_writestring(str); }

void kprintf(const char *fmt, ...) {
  char str[2048];
  va_list list;
  va_start(list, fmt);
  kvprintf(fmt, str, 2048, list);
  terminal_writestring(str);
  va_end(list);
}

void kSprintf(uint32_t serialPort, const char *fmt, ...) {
  char str[2048];
  va_list list;
  va_start(list, fmt);
  kvprintf(fmt, str, 2048, list);
  WriteStringToSerial(serialPort, str);
  va_end(list);
}

#define VPRINTF_NORMAL_LEN 0
#define VPRINTF_LONG 1
#define VPRINTF_LONG_LONG 2
#define VPRINTF_SHORT 3
#define VPRINTF_SHORT_SHORT 4

#define VPRINTF_TYPE_CHAR 0
#define VPRINTF_TYPE_STR 1
#define VPRINTF_TYPE_UNSIGNED 2
#define VPRINTF_TYPE_SIGNED 3
#define VPRINTF_TYPE_PERCENT 4

void kvprintf(const char *fmt, char *dest, size_t n, va_list list) {
  char *destBase = dest;
  while (*fmt && (uintptr_t)dest - (uintptr_t)destBase < n) {
    if (*fmt == '%') {
      fmt++;
      int length = VPRINTF_NORMAL_LEN;
      int zeroPading = 0;
      int base = 10;
      int type = -1;

      if (*fmt == 'l') {
        length = VPRINTF_LONG;
        fmt++;
        if (*fmt == 'l') {
          length = VPRINTF_LONG_LONG;
          fmt++;
        }
      }
      if (*fmt == 'h') {
        length = VPRINTF_SHORT;
        fmt++;
        if (*fmt == 'h') {
          length = VPRINTF_SHORT_SHORT;
          fmt++;
        }
      }
      if (*fmt == '0') {
        fmt++;
        fmt = str2int(fmt, &zeroPading);
      }

      switch (*fmt) {
      case '%':
        type = VPRINTF_TYPE_PERCENT;
        break;
      case 's':
        type = VPRINTF_TYPE_STR;
        break;
      case 'i':
      case 'd':
        type = VPRINTF_TYPE_SIGNED;
        break;
      case 'u':
        type = VPRINTF_TYPE_UNSIGNED;
        break;
      case 'b':
        type = VPRINTF_TYPE_UNSIGNED;
        base = 2;
        break;
      case 'o':
        type = VPRINTF_TYPE_UNSIGNED;
        base = 8;
        break;
      case 'x':
        type = VPRINTF_TYPE_UNSIGNED;
        base = 16;
        break;
      case 'c':
        type = VPRINTF_TYPE_CHAR;
        break;
      }
      fmt++;
      switch (type) {
      case VPRINTF_TYPE_CHAR: {
        char c = va_arg(list, int);
        *dest++ = c;
        break;
      }
      case VPRINTF_TYPE_STR: {
        char *str;
        str = va_arg(list, char *);
        dest++;
        strcpy(str, dest);
        dest += strlen(str);
        break;
      }
      case VPRINTF_TYPE_PERCENT:
        *dest++ = '%';
        break;
      case VPRINTF_TYPE_SIGNED: {
        intmax_t num;
        switch (length) {
        case VPRINTF_NORMAL_LEN:
          num = va_arg(list, int);
          break;
        case VPRINTF_LONG:
          num = va_arg(list, long int);
          break;
        case VPRINTF_LONG_LONG:
          num = va_arg(list, long long int);
          break;
        case VPRINTF_SHORT: {
          short int tmp = va_arg(list, int);
          num = tmp;
          break;
        }
        case VPRINTF_SHORT_SHORT: {
          char tmp = va_arg(list, int);
          num = tmp;
          break;
        }
        }

        char strNum[65];
        memset(strNum, 0, 65);
        int2str(num, base, strNum);
        if (zeroPading > 0 &&
            (unsigned)zeroPading > (strlen(strNum) - (num < 0))) {
          if (num < 0) {
            *dest = '-';
            dest++;
          }
          memset(dest, '0', zeroPading);
          strncpy(strNum + (num < 0), dest + (zeroPading - strlen(strNum)), 65);
        } else
          strncpy(strNum, dest, 65);

        dest += strlen(strNum);
        break;
      }
      case VPRINTF_TYPE_UNSIGNED: {
        uintmax_t num;
        switch (length) {
        case VPRINTF_NORMAL_LEN:
          num = va_arg(list, unsigned int);
          break;
        case VPRINTF_LONG:
          num = va_arg(list, unsigned long int);
          break;
        case VPRINTF_LONG_LONG:
          num = va_arg(list, unsigned long long int);
          break;
        case VPRINTF_SHORT: {
          unsigned short int tmp = va_arg(list, unsigned int);
          num = tmp;
          break;
        }
        case VPRINTF_SHORT_SHORT: {
          unsigned char tmp = va_arg(list, unsigned int);
          num = tmp;
          break;
        }
        }

        char strNum[65];
        memset(strNum, 0, 65);
        uint2str(num, base, strNum);
        if (zeroPading > 0 && (unsigned)zeroPading > strlen(strNum)) {
          memset(dest, '0', zeroPading);
          strncpy(strNum, dest + (zeroPading - strlen(strNum)), 65);
        } else
          strncpy(strNum, dest, 65);

        dest += strlen(strNum);
        break;
      }
      }
    } else {
      *dest++ = *fmt;
      fmt++;
    }
  }
}
