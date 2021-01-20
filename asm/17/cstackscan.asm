

section .data
	
	TopF: db "EBP-%5d: 0x%08x: 0x%08x ",10,0


section .text

%macro MPrintf 3

	push dword[%3]
	push %3
	push %2
	push %1
	call printf
	add esp, 0x10
%endmacro



GLOBAL mainASM
EXTERN printf


mainASM:

	push ebp
	mov ebp, esp
	push ebx
	push esi
	push edi
	mov esi,ebp
	mov ebx,6
	mov edi,0x00
	.jmp_here:
		MPrintf TopF,edi,esi
		add edi,4
		add esi,4
		dec ebx
		jnz .jmp_here

	
	pop edi
	pop esi
	pop ebx
	mov esp,ebp
	pop ebp
	mov eax,69
	ret
