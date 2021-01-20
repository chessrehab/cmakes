section .data
	StrMsg: db "Hello from asm!",10,0
	StrMsgLen: equ $-StrMsg


section .bss



section .text
GLOBAL ASMf



ASMf:
	push ebp
	mov ebp,esp
	push ebx
	push edi
	push esi

	mov eax,0x04
	mov ebx,0x01
	mov ecx, StrMsg
	mov edx, StrMsgLen
	int 0x80

	pop esi
	pop edi
	pop ebx
	mov esp,ebp
	pop ebp
	ret
Ex:
	mov eax, 0x01
	mov ebx,0x00
	int 0x80
