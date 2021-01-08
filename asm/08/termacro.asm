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

%macro GotoXY 2								;macro to move the cursor to YY,XX
;INPUT: al as line number (Y)=%1,ah as column number (X)=%2		;y is stored in al and x is stored in ah
;OUTPUT: nothing
;MODIFY: eax,ebx,ecx,edx
;CALLS: nothing

	pushad								;save registers on the stack

	mov ebx,eax							;duplicate input register
	and ax, 0xff							;mask out lowest byte from ax (al)
	mov cl,0x0a							;move decimal(10) constant to cl
	div cl								;divide al by decimal constant
	add %1,0x30							;add ascii(0) offset to result in al(result of division)
	mov byte[Str_move+2],%1						;move the ascii value to escape string for moving cursor
	add %2,0x30							;add ascii(0) offset to result in ah(remainder of division)
	mov byte[Str_move+3],%2						;move the ascii value to escape string for moving cursor

	mov eax,ebx							;restore eax form ebx
	shr eax,0x8							;shift right by 8 to get the higher byte (ah)
	div cl								;divide al by cl(contains decimal root constant)
	add %1,0x30							;add ascii(0) offset to result in al (result of by 10 division)
	mov byte[Str_move+5],%1						;move the ascii value to escape string for moving cursor
	add %2,0x30							;add ascii(0) offset to result in ah (remainder of the by 10 division)
	mov byte[Str_move+6],%2						;move the ascii value to escape string for moving cursor

	sys_write Str_move,Str_move_len					;calll system write kernel call and output the escape string for changing cursor position

	popad								;restore registers from the stack

%endmacro

%macro ClearScreen 0							;macro for clearing the terminal screen 
;INPUT: nothing
;OUTPUT: nothing
;MODIFY: eax,ebx,ecx,edx
;CALLS: nothing

	pushad
	sys_write Str_clear_screen,Str_clear_screen_len			;call system write kernel call and output escape string for clear screen of terminal
	popad								;restore registers from the stack

%endmacro


%macro WriteStr 1							;macro for writing a string to standard output from input buffer
;INPUT: esi as number of bytes read
;OUTPUT: nothing
;MODIFY: eax,ebx,ecx,edx
;CALLS:

	pushad								;save registers on the stack

	sys_write Buffer,%1						;call system write kernel call and output the buffer

	popad								;restore all registers from the stack
%endmacro

%macro PrintToPos 2							;macro for printing strings to specific position on terminal
;INPUT: edx as line number of terminal to output to (0Y),esi as number of bytes read
;OUTPUT: nothing
;MODIFY: eax, ecx
;CALLS: GotoXY, WriteStr

	pushad								;save registers on the stack

	xor eax, eax							;clear out eax
	mov al, %1							;copy the line position to al

	xor ecx, ecx							;clear out ecx
	mov ecx, WIDTH							;move the width of the terminal screen to ecx
	sub ecx, %2							;subtract number of bytes in the input buffer from the terminal width
	shr ecx, 0x1							;divide the result of subtraction by 2
	mov ah, cl							;move the result to ah

	GotoXY al,ah							;call macro to change terminal cursor position
	WriteStr %2							;call macro to output the buffer string to terminal

	popad								;restore all registers from stack
%endmacro


%macro ReadBuffer 0							;macro for reading from standard input to input buffer
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

%endmacro

%macro sys_write 2
	mov eax, 0x4							;setup a system write kernel call for writing the exit message
	mov ebx, 0x1							;standard output
	mov ecx, %1							;pass the address of outputed string
	mov edx, %2
	int 0x80							;execute the system call
%endmacro


_start:
	mov edx, LINE							;move the line desired line offset to edx
	ClearScreen						;clear the terminal screen
	Begin:
		ReadBuffer						;read from standard input into input buffer
		mov esi, eax						;move the number of read bytes to esi
		cmp esi, 0x0						;check if we reached end of file
		jz Ex							;if yes, jump to exit
		PrintToPos dl,esi						;if not call function to p0rint the input buffer
		inc edx							;increment the line to be printed on screen
		jmp Begin						;repeat the read to the buffer (we are not at the end of the file yet)
Ex:
	mov al,HEIGHT
	mov ah,0x0
	GotoXY al,ah							;change the cursor position
	sys_write Exit_msg,Exit_msg_len					;call system write macro to output the exit mesage

	mov eax, 0x1							;setup the exit program system call for kernel
	mov ebx, 0x0							;return value on exit
	int 0x80							;execute the system call and return to operating system
