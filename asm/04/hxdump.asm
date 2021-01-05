
section .data
	BUFF_LEN: equ 100				;length of the input buffer
	BUFF_OUT_LEN: equ (BUFF_LEN*6)+1		;length of the output buffer
	LINEBREAK: equ 8				;line break after how many bytes
	lkp: db "0123456789ABCDEF",0			;lookuptable for hex digits
	lkp_len: equ $-lkp				;length of the lookup table
	even: db 0					;counter for line breaks
section .bss
	buffer: resb BUFF_LEN				;input buffer
	buffer_out: resb BUFF_OUT_LEN			;output buffer
section .text
	global _start

_start:
	jmp read

read:
	mov eax,0x3					;system call for reading into input buffer
	mov ebx,0x0
	mov ecx,dword buffer
	mov edx,BUFF_LEN
	int 0x80
	jmp check_read					;jump to check of the system call return value


check_read:
	cmp eax,0x0					;is the return value 0? if yes, exit program, we read it all
	jz exit
	push eax					;push nr of read bytes on to the stack
	jmp write					;go to writing

write:
	pop ecx						;pop number of read bytes into ecx register
	mov edi,0x6					;output multiplication factor
	mul edi						;multiply number of bytes in eax by multiplication factor in edi
	mov edi,eax					;store the result value in edi, it is the length of the outputbuffer
	mov ebx,dword buffer				;store pointer to input buffer in ebx
	mov ebp,dword buffer_out			;store pointer to outputbuffer in ebp
	mov esi,dword lkp				;move the pointer to lookup table into esi
	.start_loop:
		movzx eax,byte [ebx]			;move the first char from input buffer to eax
		shr al,4				;mask the 4 high bits from al
		mov dh,byte [esi+eax]			;lookup the high 4 bit value in lookup table and store in dh
		movzx eax,byte [ebx]			;restore the char in eax
		and al,0xf				;mask the low 4 bits out of al
		mov dl,byte [esi+eax]			;lookup the the low 4 bits in lookup table and store in dl
		movzx eax,byte [ebx]			;restore the char in eax again
		mov byte [ebp],dh			;move the dh val to outputbuffer 
		mov byte [ebp+1],dl			;move the dl val to outputbuffer
		mov byte [ebp+2],0x28			;put "(" in outputbuffer
		mov byte [ebp+3],al			;put the char in outputbuffer
		mov byte [ebp+4],0x29			;put ")" to outputbuffer
		inc byte [even]				;increment linebreak counter
		cmp byte [even],LINEBREAK		;check if the linebreak is reached
		jz .newline				;if yes, jump to newline
		.space:
			mov byte [ebp+5],0x20		;if not, add space to outputbuffer
			jmp .conti
		.newline:
			mov byte [ebp+5],0xa		;if yes, add newline to outputbuffer
			mov byte [even],0x0		;zero out the linebreak counter
		.conti:
		inc ebx					;increment pointer to inputbuffer
		add ebp,0x6				;increment pointer to outputbuffer
		dec ecx					;decrement counter of read chars
		jnz .start_loop				;loop back again if counter not zero
	mov byte [ebp-1],0xa				;add newline char to the end of final outputbuffer
	mov eax,0x4					;print out the outputbuffer
	mov ebx,0x1
	mov ecx,dword buffer_out
	mov edx,edi
	int 0x80
	jmp read					;jump back to reading another batch of chars

exit:
	mov eax,0x1					;return system call
	mov ebx,0x0
	int 0x80



