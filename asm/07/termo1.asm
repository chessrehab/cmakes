;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; reads file chunks from standard input and outputs them in the center of the terminal;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .data

	Str_move db 27,"[YY;XXH"					;escape character string for moving cursor to YY,XX 
	Str_move_len equ $-Str_move					;length of the string
	Str_clear_screen db 27,"[2J"					;escape character string for clearing the terminal screen
	Str_clear_screen_len equ $-Str_clear_screen			;length of the string
	Exit_msg db 10,"Exited gracefully,bye...",10			;exit message string
	Exit_msg_len equ $-Exit_msg					;exit message string length
	
	LINE equ HEIGHT/2						;YY offset of the cursor
	WIDTH equ 80							;width of the terminal screen
	HEIGHT equ 24							;height of the terminal screen


section .bss
	BUFF_LEN equ 50							;length of the read buffer chunk
	Buffer resb BUFF_LEN						;buffer memory allocation


section .text

GLOBAL _start

GotoXY:									;function to move the cursor to YY,XX
;INPUT: al as line number (Y),ah as column number (X)			;y is stored in al and x is stored in ah
;OUTPUT: nothing
;MODIFY: eax,ebx,ecx,edx
;CALLS: nothing

	pushad								;save registers on the stack

	mov ebx,eax							;duplicate input register
	and ax, 0xff							;mask out lowest byte from ax (al)
	mov cl,0x0a							;move decimal(10) constant to cl
	div cl								;divide al by decimal constant
	add al,0x30							;add ascii(0) offset to result in al(result of division)
	mov byte[Str_move+2],al						;move the ascii value to escape string for moving cursor
	add ah,0x30							;add ascii(0) offset to result in ah(remainder of division)
	mov byte[Str_move+3],ah						;move the ascii value to escape string for moving cursor

	mov eax,ebx							;restore eax form ebx
	shr eax,0x8							;shift right by 8 to get the higher byte (ah)
	div cl								;divide al by cl(contains decimal root constant)
	add al,0x30							;add ascii(0) offset to result in al (result of by 10 division)
	mov byte[Str_move+5],al						;move the ascii value to escape string for moving cursor
	add ah,0x30							;add ascii(0) offset to result in ah (remainder of the by 10 division)
	mov byte[Str_move+6],ah						;move the ascii value to escape string for moving cursor

	mov eax,0x4							;setup system write kernel call
	mov ebx,0x1
	mov ecx, Str_move						;escape string for moving cursor
	mov edx, Str_move_len
	int 0x80							;write the escape string for moving cursor to standard output

	popad								;restore registers from the stack

	ret

ClearScreen:								;function for clearing the terminal screen 
;INPUT: nothing
;OUTPUT: nothing
;MODIFY: eax,ebx,ecx,edx
;CALLS: nothing

	pushad								;save all registers on the stack
	mov eax, 0x4							;setup the system write kernel call
	mov ebx, 0x1
	mov ecx, Str_clear_screen					;pass the escape string for clearing the terminal screen
	mov edx, Str_clear_screen_len
	int 0x80							;clear the terminal screen
	popad								;restore registers from the stack

	ret


WriteStr:								;function for writing a string to standard output from input buffer
;INPUT: esi as number of bytes read
;OUTPUT: nothing
;MODIFY: eax,ebx,ecx,edx
;CALLS:

	pushad								;save registers on the stack

	mov eax,0x4							;setup system write kernel call
	mov ebx, 0x1
	mov ecx, Buffer							;pass the buffer address to system call
	mov edx, esi							;pass the number of bytes that were read to buffer
	int 0x80							;execute the system call

	popad								;restore all registers from the stack
	
	ret

PrintToPos:								;function for printing strings to specific position on terminal
;INPUT: edx as line number of terminal to output to (0Y),esi as number of bytes read
;OUTPUT: nothing
;MODIFY: eax, ecx
;CALLS: GotoXY, WriteStr

	pushad								;save registers on the stack

	xor eax, eax							;clear out eax
	mov al, dl							;copy the line position to al

	xor ecx, ecx							;clear out ecx
	mov ecx, WIDTH							;move the width of the terminal screen to ecx
	sub ecx, esi							;subtract number of bytes in the input buffer from the terminal width
	shr ecx, 0x1							;divide the result of subtraction by 2
	mov ah, cl							;move the result to ah

	call GotoXY							;call the function to set the terminal cursor position
	call WriteStr							;write the input buffer string to the position

	popad								;restore all registers from stack
	ret


ReadBuffer:								;function for reading from standard input to input buffer
;INPUT: nothing
;OUTPUT: eax as number of bytes read
;MODIFY: eax,ebx,ecx,edx
;CALLS: nothing


	push ebx							;save some registers on the stack
	push ecx
	push edx
	mov eax, 0x3							;setup system read kernel call
	mov ebx, 0x0
	mov ecx, Buffer							;pass the address of the input buffer
	mov edx, BUFF_LEN
	int 0x80							;execute the system call
	pop edx								;restore saved registers
	pop ecx
	pop ebx

	ret

_start:
	mov edx, LINE							;move the line desired line offset to edx
	call ClearScreen						;clear the terminal screen
	Begin:
		call ReadBuffer						;read from standard input into input buffer
		mov esi, eax						;move the number of read bytes to esi
		cmp esi, 0x0						;check if we reached end of file
		jz Ex							;if yes, jump to exit
		call PrintToPos						;if not call function to p0rint the input buffer
		inc edx							;increment the line to be printed on screen
		jmp Begin						;repeat the read to the buffer (we are not at the end of the file yet)
Ex:
	mov al, HEIGHT							;set the yy poistion on the bottom of the terminal
	mov ah, 0x0							;set the XX position on the begining of line
	call GotoXY							;change the cursor position
	mov eax, 0x4							;setup a system write kernel call for writing the exit message
	mov ebx, 0x1
	mov ecx, Exit_msg						;pass the address of the exit message
	mov edx, Exit_msg_len
	int 0x80							;execute the system call


	mov eax, 0x1							;setup the exit program system call for kernel
	mov ebx, 0x0							;return value on exit
	int 0x80							;execute the system call and return to operating system
