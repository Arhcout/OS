
.global reloadSegments
reloadSegments:
   // Reload CS register containing code selector:
	pushl $0x8
	push $.reload_CS
  ljmp *(%esp) // 0x08 is a stand-in for your code segment
.reload_CS:
	// restor stack
	add $8, %esp

	// Reload data segment registers:
	mov   $0x10, %ax // 0x10 is a stand-in for your data segment
	mov   %ax, %ds
	mov   %ax, %es
	mov   %ax, %fs
	mov   %ax, %gs
	mov   %ax, %ss
	ret
