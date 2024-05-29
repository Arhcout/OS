 idtr:.short 0 // For limit storage
      .long  0 // For base storage
 
.global setIdt
setIdt:
	mov 4(%esp), %ax
	mov %ax, idtr
	mov 8(%esp), %eax
	mov %eax, 2+idtr
	lidt (idtr)
	ret


