
section .data
	Test_msg: db "This is a test message."
	Test_msg_len: equ $-Test_msg
	Exit_msg: db 10,"...Exited gracefully...",10
        Exit_msg_len equ $-Exit_msg
	WIDTH: equ 81
	HEIGHT: equ 25

section .bss
	Video_buf resd WIDTH*HEIGHT


section .text
GLOBAL _start
GLOBAL Video_buf
EXTERN Show,Clear,Write_str,Write_rul,Write_bar


_start:
	cld						;clear the direction flag for upwards string manipulation
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
	mov eax,0x1					;exit program gracefully
	mov ebx,0x0
	int 0x80
