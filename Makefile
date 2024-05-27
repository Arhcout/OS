include Makefile.in

OBJ:=

.PHONY: os run clean

os:
	$(MAKE) -C kernel kernel
	#$(MAKE) -C libc
	OBJS=$$(cat kernel/kernelobj.txt);\
	echo $$OBJS;\
	$(CC) -T kernel/arch/$(TARGET)/linker.ld -o $(NAME).bin -ffreestanding -O2 -nostdlib $$OBJS -lgcc
	if grub-file --is-x86-multiboot MyOs.bin; then\
 		echo multiboot confirmed;\
	else\
  	echo the file is not multiboot;\
	fi
	mkdir -p isodir/boot/grub
	cp $(NAME).bin isodir/boot/$(NAME).bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $(NAME).iso isodir

run:
	qemu-system-i386 -cdrom $(NAME).iso

debug:
	qemu-system-i386 -s -S -kernel $(NAME).bin

clean:
	rm -f $$(find . -name '*.o')
	rm -rf isodir

