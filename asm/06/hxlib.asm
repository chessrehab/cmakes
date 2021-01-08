

section .data
	hxdump_line: db "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "				;buffer for output
	hxdump_line_len: equ $-hxdump_line								;outputbuffer length
	ascii_line: db "|................|",10								;ascii part of buffer
	ascii_line_len: equ $-ascii_line								;ascii part of buffer length
	line_len: equ $-hxdump_line									;full outputbuffer length
	hxdigit: db "0123456789ABCDEF"									;lookup table for hex digits
	ascii: db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E	;ascii lookup table
	       db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
	       db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
	       db 0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E
	       db 0x2E,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F
	       db 0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x2E,0x2E,0x2E,0x2E,0x2E
	       db 0x2E,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F
	       db 0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x2E,0x2E,0x2E,0x2E,0x2E

section .bss
	WIDTH: equ 16
section .text

GLOBAL ClearLines,DumpChar,PrintLine					;export functions


ClearLines:								;function to clear output buffer

;INPUT:nothing
;OUTPUT:nothing
;CHANGES:ecx,eax

	push ecx
	push eax
	xor eax,eax
	mov ecx,WIDTH-1							;setting counter for clearing loop
	mov al,0x30							;move dot in al register
	.start_loop:
		call DumpChar						;call function to insert char
		dec ecx							;decrement loop counter
		jnz .start_loop						;start another loop cycle
	pop eax								;restore affected registers
	pop ecx
	ret
DumpChar:								;function to insert single character/byte to output buffer (both hex digit and ascii)

;INPUT: ecx:position of char tu dump, eax/al:byte to dump
;OUTPUT: nothing
;CHANGES: ebx,edx

	push eax
	push ebx
	push edx
	xor ebx,ebx
	xor edx,edx
	mov bl,al;							;duplicate the input value
	shr al,0x4							;shift the high nibble
	mov dl,byte [hxdigit+eax]					;lookup the nibble in hex digit lkp table
	mov byte [hxdump_line+ecx*3],dl					;move the digit to output buffer
	mov al,bl							;restore the al register from bl
	and al,0x0f							;mask out the low nibble
	mov dl,byte [hxdigit+eax]					;lookup the low nibble in the hexdigit lkp table
	mov byte [hxdump_line+ecx*3+1],dl				;store the looked up hex digit in the outputbuffer
	mov dl,byte [ascii+ebx]						;lookup the ascii value in ascii table for the dumped char/byte
	mov byte [ascii_line+ecx+1],dl					;store the ascii value in the output buffer
	pop edx								;restore registers
	pop ebx
	pop eax
	ret
PrintLine:								;function to printout the outputbuffer 

;INPUT:nothing
;OUTPUT:nothing
;CHANGES:eax,ebx,ecx,edx

	pushad
	mov eax,0x4
	mov ebx,0x1
	mov ecx,hxdump_line
	mov edx,line_len
	int 0x80
	popad
	ret

