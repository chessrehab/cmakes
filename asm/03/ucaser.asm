
section .data
	buff_len equ 10					;define length of buffer
	msg_succ db "all went successfully",10,0	;success message
	msg_succ_len equ $-msg_succ			;define length of success message
	msg_err db "error appeared",0			;define error message
	msg_err_len equ $-msg_err			;define length of error message

section .bss
	buffer resb buff_len				;reserve buffer with defined length
	buff_read resd  1  				;reserve integer to carry number of read characters on one read

section .text
	global _start

_start:
	jmp read					;jump to reading of the file
	
read:
	mov eax,0x3					;set the number of system call for reading
	mov ebx,0x0					;set the file descriptor for readin (stdin)
	mov ecx,buffer					;set the address of the buffer to read to
	mov edx,buff_len				;set the number of chars to be read
	int 0x80					;call the software interrupt
	jmp check_read_return				;jump to read cheeck routine



write:
	pop dword [buff_read]				;pop the number of read bytes to variable buff_read
	mov ecx, dword [buff_read]			;put the number of read bytes to counter register
	mov ebx, dword buffer				;put the address of the read buffer to ebx
	
	.start_loop:
		cmp byte [ebx],0x61			;compare the pointed character to begining of lowercase ascii
		jb .next_loop				;if smaller means that char is not lowercase and can move to next char
		cmp byte [ebx],0x7a			;compare the pointed character to end of lowercase ascii
		ja .next_loop				;if bigger means that char is not lowercase and can proceed to next char
		sub byte [ebx],0x20			;the char is lowercase and subtract 32 to make it uppercase
	.next_loop:
		inc ebx					;increment the buffer char pointer to next char
		dec ecx					;decrement the char counter
		jnz .start_loop				;if there are chars left loop again 
	mov eax,0x4					;set the number of write system call to 4
	mov ebx,0x1					;set the write file descriptor (stdout)
	mov ecx,dword buffer				;set the address of the buffer to be written
	mov edx,dword [buff_read]			;set the number of chars to be written
	int 0x80					;call the software interrupt
	jmp read					;go back to reading next batch

check_read_return:
	cmp eax,0x0					;check the number of bytes read
	jz exit						;if zero means we are at the end of file and go to exit
	push eax					;push the number of read chars to stack
	jmp write					;go to writing procedure

exit:
	mov eax,0x4					;set the number of system call to 4(sys_write)
	mov ebx,0x2					;set the output file descriptor (stderr)
	mov ecx,msg_succ				;set the addreess of the succ_msg buffer for system call
	mov edx,msg_succ_len				;set the length of the buffer to be output
	int 0x80					;execute the system call (sys_write)
	mov eax,0x1					;set the number of system call (exit)
	mov ebx,0x0					;set the return value for exit
	int 0x80					;execute systemcall

