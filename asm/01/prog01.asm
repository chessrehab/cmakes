




; nasm -f elf -F stabs -g prog01.asm
; ld -o sndbx prog01.o ;doesnt work on 64bit architecture, can be used for 32bit processor
; ld -m elf_i386 -s -o sndbx prog01.o ;works on 64bit architecture




section .data                               ;initialized global variables area
	otpt db "Hello from ASM\n",10               ;definition of a string, with pointer otpt pointing to first byte
	otpt_len equ $-otpt                     ;definition of a constant for string length calculated from the memory pointer minus first byte of string
	val1 dud  128
	val2 dd  128

section .bss                                ;uninitialized global variables area

section .text                               ;text of code area
	global _start                           ;entry point defining label entry point of code

_start:                                     ;label entry point
	nop                                     ;no operation, point for debugger to stop
;.............................................................................................sandbox
	mov eax,0FFFFFFFFh

	mov ecx,val1
	mov ecx,0
	movzx ecx,BYTE [val1]
	neg BYTE [val1]
	neg BYTE [val1]
	inc ecx
	mov ecx, 8
;	mov [val1],ecx
	add BYTE [val1],1
	sub [val1],DWORD 9
	dec DWORD [val1]
	nop
	add DWORD [val1], 2
	mov ecx,DWORD [val1]
	sub ecx,6
;	inc [ecx]
;..............................................................................................sandbox
	jmp .fnct
.fnct:
	mov eax,04h                             ;move code for output(4) linux api system call into eax register
	mov ebx,01h                             ;move fd number for stdout operation to eax register
	mov ecx,otpt                            ;move a pointer to first char byte for stdout into ecx register
	mov edx,otpt_len                        ;move a string length variable to edx register
	int 080h                                ;call linux system call (software interrupt)
	jmp _exit


	nop                                     ;no operation, point for debugger to stop

_exit:
	mov eax,1                               ;move code for exit(1) linux system call into eax register
	mov ebx,0                               ;move program return value to register ebx
	int 80h                                 ;call linux api system call(software interrupt)

 


; system call 4 -write to output (eax=4, ebx=fd for output, ecx= char * pointer, edx= string length of the pointer)
; system call 1 -exit  (eax=1, ebx= return value)

