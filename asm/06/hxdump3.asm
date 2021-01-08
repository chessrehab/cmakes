

section .data

        exit_msg: db 10," ..all finished!!",10				;exit message
	exit_msg_len: equ $-exit_msg					;exit message length

section .bss
	WIDTH equ 16							;width of output
	buffer: resb WIDTH						;buffer for reading data
	buffer_len: equ $-buffer					;length of input buffer

section .text

GLOBAL _start
EXTERN ClearLines,DumpChar,PrintLine					;import functions from library



LoadBuffer:								;function to read the string into input buffer

;INPUT:nothing
;OUTPUT:eax:number of chars read
;CHANGES:ebx,ecx,edx

	push ebx
	push ecx
	push edx
	mov eax,0x3
	mov ebx,0x0
	mov ecx,buffer
	mov edx,buffer_len
	int 0x80
	pop edx
	pop ecx
	pop ebx
	ret

_start:
	.begin:								;begin reading new buffer
	call ClearLines							;clear out output buffers
	call LoadBuffer							;read string to input buffer
	cmp eax,0x0
	jz Ex
	mov edi,eax							;eax returns nr of bytes read from load
	.scan:								;scan the loaded buffer
		movzx eax,byte [buffer+edi-1]				;move 1 read byte to eax
		mov ecx,edi						;edi stores the decrementing counter, replicate it to ecx
		dec ecx
		call DumpChar						;dump the char into output buffers
		dec edi							;decrement counter
		jnz .scan						;check if we reached end of buffer
	call PrintLine							;when at the end of buffer print the outputbuffer to output
	jmp .begin							;go back to reading a new input buffer

Ex:									;exit: write out exit message and return

	mov eax,0x4
	mov ebx,0x1
	mov ecx,exit_msg
	mov edx,exit_msg_len
	int 0x80

	mov eax,0x1
	mov ebx,0x0
	int 0x80
