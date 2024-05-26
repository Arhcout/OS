include ../Makefile.in

ARCH_DIR=arch/$(TARGET)

CRTI_OBJ=$(CURDIR)/$(ARCH_DIR)/crti.s.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=$(CURDIR)/$(ARCH_DIR)/crtn.s.o

KERNEL_SRC=$(shell find ~+ -name *.c)
KERNEL_OBJ=$(KERNEL_SRC:%=%.o)

.PHONY: kernel

kernel: $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(CURDIR)/arch/$(TARGET)/boot.s.o $(KERNEL_OBJ) $(CRTEND_OBJ) $(CRTN_OBJ)
	@echo $^ > kernelobj.txt

%.c.o: %.c
	$(CC) -c $^ -o $@ $(KERNEL_CFLAGS)

%.s.o: %.s
	$(AS) $^ -o $@
