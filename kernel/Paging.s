
.text
.global EnablePaging
EnablePaging:
	mov 4(%esp), %eax
	mov %eax, %cr3
	mov %cr0, %eax
	or $0x80000001, %eax
	mov %eax, %cr0
	ret
