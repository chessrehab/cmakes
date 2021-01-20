

section .data
	
	Empty: db "%d:%d:%s",0
	Line: db "---------------------------------------------------",10,0
	Line_len: equ $-Line
	TopF: db "EBP-%5d: 0x%08x: 0x%08x",10,0
	ArgStr: db "Argument: %s",10,0
	EnvStr: db "Enviromental: %s",10,0


section .text

%macro MPrintf 3
	push dword[%3]
	push %3
	push %2
	push %1
	call printf
	add esp, 0x10
%endmacro


%macro MPrintfs 1
	push edi
	push  %1
	call printf
	add esp, 0x08
%endmacro


GLOBAL main
EXTERN printf


main:

	push ebp
	mov ebp, esp
	push ebx
	push esi
	push edi
	mov esi,ebp
	mov ebx,5
	mov edi,0x00
	.jmp_here:
		
		MPrintf TopF,edi,esi
		add edi,4
		add esi,4
		dec ebx
		jnz .jmp_here
	
	mov ebx,0x0
	mov esi,dword[ebp+12]		;in esi we have address of pointer table
	.jmp_here2:
				
		mov edi,dword[esi+ebx*4]
		MPrintfs ArgStr
		inc ebx
		cmp ebx,dword[ebp+8]
		jnz .jmp_here2
	mov ebx,0
	mov esi,dword[ebp+16]
	.jmp_here3:
		mov edi,dword[esi+ebx*4]
		MPrintfs EnvStr
		inc ebx
		cmp edi,0
		jnz .jmp_here3

	pop edi
	pop esi
	pop ebx
	mov esp,ebp
	pop ebp
	ret
