include ../Makefile.in

KERNEL_SRC=$(shell find ~+ -name *.c)
KERNEL_OBJ=$(KERNEL_SRC:%=%.o)

.PHONY: kernel

kernel: $(CURDIR)/arch/$(TARGET)/boot.s.o $(KERNEL_OBJ)
	@echo $^ > kernelobj.txt

%.c.o: %.c
	$(CC) -c $^ -o $@ $(KERNEL_CFLAGS)

%.s.o: %.s
	$(AS) $^ -o $@
