


section .data
	Msg: db 10,"..puts:hello from C...",10,0
	Msg_len: equ $-Msg
	Msg2: db 10,"...hello- %d.time from c, this time from %s function!",10,0
	Msg2_len: equ $-Msg2
	Fct: db " PRINTF ",0
	Fct_len: equ $-Fct
	Itime: dd 0x00000002

section .bss

section .text

GLOBAL main
EXTERN puts,fgetc
;EXTERN printf,fprintf
EXTERN stdin,stdout


main:
	push ebp
	mov ebp,esp
	push ebx
	push esi
	push edi

	push Msg
	call puts
	add esp,4

;	push Fct
;	push dword[Itime]
;	push Msg2
;	call printf
;	add esp,12

;	inc dword[Itime]
;	push Fct
;	push dword[Itime]
;	push Msg2
;	push dword[stdout]
;	call fprintf
;	add esp,16

	push dword[stdin]
	call fgetc
	add esp,4

	pop edi
	pop esi
	pop ebx
	mov esp,ebp
	pop ebp
	ret


