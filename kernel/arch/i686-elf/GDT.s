gdtr: .short 0 // For limit storage
      .long  0 // For base storage
 
.global setGdt
setGdt:
	mov 4(%esp), %ax
	mov %ax, gdtr
	mov 8(%esp), %eax
	mov %eax, 2+gdtr
	lgdt (gdtr)
	ret

