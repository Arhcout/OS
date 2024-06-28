.section .multiboot
multiboot2_header_start:
/* magic number */
.long   0xe85250d6
/* architecture */
.long   0
/* header size */
.long   multiboot2_header_end - multiboot2_header_start
/* checksum */
.long   -(0xe85250d6 + (multiboot2_header_end - multiboot2_header_start))

/* tag end */
.align 8
.short   0
.short   0
.long   8
multiboot2_header_end:

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp

	call _init

	call kernel_main

	call _fini

	cli
1:	hlt
	jmp 1b

/*
Set the size of the _start symbol to the current location '.' minus its start.
This is useful when debugging or when you implement call tracing.
*/
.size _start, . - _start
