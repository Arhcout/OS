.section .multiboot
multiboot2_header_start:
.align 8
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

.section .boot_bss
.align 16
boot_stack_bottom:
.skip 16384
boot_stack_top:

.section .boot_text
.global _start
.type _start, @function
_start:
	mov $boot_stack_top, %esp

  push %eax
  push %ebx

	call EarlyKernel
  
	mov %eax, %cr3
	mov %cr0, %eax
	or $0x80000001, %eax
	mov %eax, %cr0

  pop %ebx
  pop %eax
  # Jump to higher half with an absolute jump. 
	lea high_kernel, %ecx
	jmp *%ecx

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.extern kernel_main
high_kernel:
	mov $boot_stack_top, %esp

	call _init

  jmp kernel_main

	call _fini

	cli
1:	hlt
  jmp 1b
