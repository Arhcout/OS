include Makefile.in

OBJ:=

.PHONY: os run clean

os:
	$(MAKE) -C kernel kernel
	#$(MAKE) -C libc
	OBJS=$$(cat kernel/kernelobj.txt);\
	$(CC) -T kernel/linker.ld -o $(NAME).bin -ffreestanding -g -nostdlib $$OBJS -lgcc
	if grub-file --is-x86-multiboot2 MyOs.bin; then\
 		echo multiboot confirmed;\
	else\
  	echo the file is not multiboot;\
	fi
	mkdir -p isodir/boot/grub
	cp $(NAME).bin isodir/boot/$(NAME).bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(NAME).iso isodir

run: os
	qemu-system-i386 -cdrom $(NAME).iso -serial pty & putty

debug: os
	qemu-system-i386 -s -S -cdrom $(NAME).iso -serial pty & putty &
	gdb $(NAME).bin

clean:
	rm -f $$(find . -name '*.o')
	rm -rf isodir

