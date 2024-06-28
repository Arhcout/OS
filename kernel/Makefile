include ../Makefile.in

ARCH_DIR=arch/$(TARGET)

CRTI_OBJ=$(CURDIR)/$(ARCH_DIR)/crti.s.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=$(CURDIR)/$(ARCH_DIR)/crtn.s.o

ARCH_SRC=$(shell find ~+/arch/$(TARGET) -name '*.c' -or -name '*.s')
KERNEL_SRC=$(shell find ~+ -name '*.c' | grep -v arch) $(ARCH_SRC)
KERNEL_OBJ=$(KERNEL_SRC:%=%.o)

.PHONY: kernel

kernel: $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(CURDIR)/arch/$(TARGET)/boot.s.o $(KERNEL_OBJ) $(CRTEND_OBJ) $(CRTN_OBJ)
	@echo $^ > kernelobj.txt

%.c.o: %.c
	if grep -q "isr" <<< "$^"; then\
		SPECIAL_FLAGS="-mgeneral-regs-only -mno-red-zone";\
	fi;\
	$(CC) -c $^ -o $@ $(KERNEL_CFLAGS) $$SPECIAL_FLAGS

%.s.o: %.s
	$(AS) $^ -o $@ $(ASMFLAGS)
