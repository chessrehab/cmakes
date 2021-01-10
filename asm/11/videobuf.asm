
section .data
	Exit_msg: db 10,"...Exited gracefully...",10
        Exit_msg_len equ $-Exit_msg
	WIDTH: equ 81
	HEIGHT: equ 25
	ASCII_LEN: equ 127- ASCII_START
	ASCII_START: equ 32
	START_Y: equ 10
	START_X: equ 20
	LEN: equ 32 

section .bss
	Video_buf resd WIDTH*HEIGHT


section .text
GLOBAL _start
GLOBAL Video_buf
EXTERN Show,Clear,Write_str,Write_rul,Write_bar

Draw_rulers:
;INPUT:nothing
;OUTPUT:nothing
;MODIFIES:eax,ebx,ecx
;CALLS: Write_rul


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

	ret

Print_ascii:
;INPUT: EAX (Y-row to start printing), EBX (X-column to start printing at), EDX (number of chars per line)
;OUTPUT:nothing
;MODIFIES: eax,edi,esi,ebp,edx,ecx,df
;CALLS: nothing

	pushad						;backup all the registers on stack
	pushfd						;backup all the flags on stack
	cld
	mov ecx, ASCII_LEN				;move the interval of ascii table to ecx (counter overall)
	mov edi, Video_buf				;put the address of a video buffer to edi
	mov ah, WIDTH					;move the buffer row width to ah
	mul ah						;multiply the row width with number of rows where the table will start to eax
	add ax, bx					;add x coordinate to calculated value
	add edi, eax					;offset the dest index by the calculated value
	mov al, ASCII_START				;starting character of desired ascii inreval
	mov esi, ebx					;put the x coordinate to esi
	add esi, edx					;add the width of ascii row to esi
	mov ebp, WIDTH					;put video buffer width to ebp
	sub ebp, esi					;subtract the end of ascii row from row width
	add ebp, ebx					;add x coordinate to ebp
	mov esi, ebp					;move the final offset to esi
	mov ebp, edx					;replicate ascii row length in ebp as backup
	jmp .doChar					;jump to start of char pushing
	.doLine:
	mov edx, ebp					;restore edx column counter from ebp
	add edi, esi					;add offfset for start of next line to dest index
	.doChar:
	stosb						;punch a char to det index
	inc al						;increment the content char to next char
	dec edx						;decrement the column counter
	loopnz .doChar					;decrement the ecx overall counter and check the zero flag for end of column counter
	jcxz .finish					;if overall counter done jump to finish
	jmp .doLine					;if only column counter done jump to do the next line

	.finish:
	popfd						;restore all flags from stack
	popad						;restore all registers from stack
	ret


_start:
	cld						;clear the direction flag for upwards string manipulation
	call Clear					;clear the video buffer and initialize newline chars

	mov eax, START_Y				;set the print ascii function input (y coordinate)
	mov ebx, START_X				;set the print ascii function input (x coordinate)
	mov edx, LEN					;set the print ascii function input (table width)
	call Print_ascii				;execute the print ascii function
	call Draw_rulers				;draw rulers
	call Show					;print the video buffer to screen
	jmp Ex						;jump tp exit


Ex:
	mov eax,0x1					;exit program gracefully
	mov ebx,0x0
	int 0x80
