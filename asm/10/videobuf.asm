
section .data
	Str_move db 27,"[YY;XXH"                                        ;escape character string for moving cursor to YY,XX 
        Str_move_len equ $-Str_move                                     ;length of the string
        Str_clear_screen db 27,"[2J"                                    ;escape character string for clearing the terminal screen
        Str_clear_screen_len equ $-Str_clear_screen                     ;length of the string
	Test_msg: db "This is a test message."
	Test_msg_len: equ $-Test_msg
	Exit_msg: db 10,"...Exited gracefully...",10
        Exit_msg_len equ $-Exit_msg
	WIDTH: equ 81
	HEIGHT: equ 24


section .bss
	Video_buf resd WIDTH*HEIGHT


section .text
GLOBAL _start
%include "./lib/libmacro.incl"				;contains macros for exititing program (Exit_program 1) and printing to standard output (Print_out 2)

Show: ;fin						;function that displays the video buffer on standard output
;INPUT:nothing
;OUTPUT:nothing
;MODIFIES:nothing
;CALLS:Print_out

	Print_out Video_buf, WIDTH*HEIGHT		;calls macro for sys write system call
	ret

Clear: ;fin						;function that clears out the video buffer and adds \n at the end of each line
;INPUT:nothing
;OUTPUT:nothing
;MODIFIES:eax,ecx,edi
;CALLS:nothing

	pushad						;backup registers on the stack
	mov al, 0x20					;put space in al
	mov ecx, WIDTH*HEIGHT				;set the counter for the video buffer length
	mov edi,Video_buf				;put the address of the video buffer to destination index
	rep stosb					;fire spaces into whole video buffer

	mov edi, Video_buf				;reset destination index to begining of the video buffer
	mov ecx, HEIGHT					;set the counter for number of rows
	mov al, 0x0a					;put newline char to al
	.start_loop:					;loops through rows
		mov byte[edi+WIDTH-1],al		;put LF char to end of each row
		add edi,WIDTH				;increment destination index to next row 
	loop .start_loop
	popad						;restore registers from the stack
	ret

Write_str: ;fin						;function to write string of chars to Y,X coordinates
;INPUT:ESI (source string address), EAX (Y-row), EBX (X-column), ECX (string length)
;OUTPUT:nothing
;MODIFIES: eax,edi,ecx,Video_buf
;CALLS: nothing

	pushad						;backup all registers on stack
	mov ah, WIDTH					;put row width into ah
	mul ah						;multiply al * ah and store result in ax
	add eax, ebx					;add column offset to row offset
	lea edi, [Video_buf+eax]			;load the calculated address to destination index
	rep movsb					;fire up bytes from source index to destination index
	popad						;restore all registers from stack
	ret

Write_bar: ;fin						;function that writes same character to X,Y coordinates, ebp stores the desired byte
;INPUT: EAX (Y-row), EBX (X-ropw), ECX (length of the bar), EBP (byte to compose the bar with) 
;OUTPUT: nothing
;MODIFIES: eax,edi, Video_buf
;CALLS: nothing

	pushad						;backup all registers on the stack
	mov ah, WIDTH					;move row width to ah 
	mul ah						;multiply al * ah and store result in ax
	add eax, ebx					;add column offset to row offset
	lea edi, [Video_buf+eax]			;load address of the offset to destination index
	mov eax, ebp					;move the content char byte to al
	rep stosb					;fire the bytes to destination index
	popad						;restore registers from stack

	ret

Write_rul:						;function that writes horizontal or vertical rulers to video buffer
;INPUT: EAX (index-x or y), EBX (0=horizontal, 1=vertical)
;OUTPUT: nothing
;MODIFIES: ebx,eax,ecx, edi,Video_buf
;CALLS: nothing

	pushad						;backup all registers on the stack
	cmp ebx, 0x0					;check if we gonna do horizontal or vertical ruler
	jnz .vertical					;if vertical jump to vertical

	.horizontal:
	mov ah, WIDTH					;if horizontal move row width to ah
	mul ah						;multiply al * ah and store result in ax
	lea edi, [Video_buf+eax]			;put the row offset address to destination index
	xor eax,eax					;zero out eax 
	mov al, '0'					;put the 0 ascii char to al
	mov ecx, WIDTH-1				;setup the counter for ruler length
	.lph:
	stosb						;store ruler index in destination index
	add al,'1'					;perform bcd increment of ruler index
	aaa
	or al, 0x30					;add the 30 to higher nibble of al for ascii code generation
	loop .lph					;move to the next char in ruler
	jmp .finish					;jump to finish

	.vertical:
	mov ebx, eax					;if vertical store y coordinate in ebx
	mov al,'0'					;set the initial ruler index char to ascii 0
	mov ecx, HEIGHT					;set up the counter for nr of chars in the vertical ruler= height of screen
	lea edi, [Video_buf]				;setup destination index to the start of video buffer
	.lpv:
	mov byte[edi+ebx],al				;move ruler index char to video buffer
	add al, '1'					;increment ruler index char using BCD
	aaa
	or al, 0x30					;set the higher nibble of al byte to 0x3 for ascii encoding
	add edi, WIDTH					;increment the destination index by one row of chars
	loop .lpv					;process another ruler char

	.finish:
	popad						;restore all registers from the stack
	ret

_start:

	call Clear					;clear the video buffer and initialize newline chars
	mov eax,0x0c					;setup the X coordinate in eax
	mov ebx,0x28					;setup the Y coordinate in ebx
	mov esi, Test_msg				;setup the source index with address of the test msg
	mov ecx, Test_msg_len				;setup ecx with test msg lenth
	call Write_str					;write the test msg to video buffer

	mov eax,0x0d					;set the Y coordinate for bar
	mov ebx,0x0a					;set the X coordinate for bar
	mov ecx,0x14					;set the length of the bar
	mov ebp,0x3d					;set the byte to be the bar content
	call Write_bar					;write the bar to video buffer

	mov eax, 0x00					;set the rownumber (Y) for drawing the ruler
	xor ebx,ebx					;choose the horizonatl ruler
	call Write_rul					;write the ruler to video buffer

	mov eax, 0x00					;set the column number for drawing ruler
	mov ebx, 0x01					;choose vertical ruler
	call Write_rul					;write the ruler to video buffer

	mov eax, HEIGHT-1				;set the y coordinate (row) for bottom horizontal ruler
	xor ebx,ebx					;choose horizontal ruler
	call Write_rul					;write the ruler to the video buffer

	mov eax, WIDTH-2				;set the  x coordinate (column) number
	mov ebx, 0x01					;choose vertical ruler
	call Write_rul					;write the ruler to video buffer

	call Show					;print the video buffer to screen
	jmp Ex						;jump tp exit






Ex:
	Exit_program 0					;exit program gracefully
