




; nasm -f elf -F stabs -g prog01.asm
; ld -o sndbx prog01.o ;doesnt work on 64bit architecture, can be used for 32bit processor
; ld -m elf_i386 -s -o sndbx prog01.o ;works on 64bit architecture




section .data                               ;initialized global variables area
	otpt: db "Hello from ASM",10               ;definition of a string, with pointer otpt pointing to first byte
	otpt_len: equ $-otpt                     ;definition of a constant for string length calculated from the memory pointer minus first byte of string
	val1: dd  128
	val2: dd  4

;section .bss                                ;uninitialized global variables area
	val3 dd

section .text                               ;text of code area
	global _start                           ;entry point defining label entry point of code

_start:                                     ;label entry point
	nop                                     ;no operation, point for debugger to stop
;.............................................................................................sandbox
	mov al,06h
	add dword [val2], eax
	mov eax,dword [val2]
	push ax
	push eax
	push word [val2]
	pop dx
	pop dword [val3]
	pushf
	popf 
	push 00400h
	popfd
	mov eax,6
	mov ecx,7
	mov edx,8
	mov ebx,9
	mov ebp,10
	mov esi,11
	mov edi,12
	pushad
	popad





	nop
;..............................................................................................sandbox
	jmp .fnct
.fnct:
	mov eax,04h                             ;move code for output(4) linux api system call into eax register
	mov ebx,01h                             ;move fd number for stdout operation to eax register
	mov ecx,otpt                            ;move a pointer to first char byte for stdout into ecx register
	mov edx,otpt_len                        ;move a string length variable to edx register
	int 080h                                ;call linux system call (software interrupt)
	jmp .exit


	nop                                     ;no operation, point for debugger to stop

.exit:
	mov eax,1                               ;move code for exit(1) linux system call into eax register
	mov ebx,0                               ;move program return value to register ebx
	int 80h                                 ;call linux api system call(software interrupt)
	nop
 


; system call 4 -write to output (eax=4, ebx=fd for output, ecx= char * pointer, edx= string length of the pointer)
; system call 1 -exit  (eax=1, ebx= return value)

