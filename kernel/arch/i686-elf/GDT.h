#ifndef GDT_H
#define GDT_H

#define GDT_K_CODE_OFF 0x8
#define GDT_K_DATA_OFF 0x10
#define GDT_C_CODE_OFF 0x18
#define GDT_C_DATA_OFF 0x20

void InitGDT();

#endif
