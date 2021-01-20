

section .data
	MAXLINE: equ 100
	NULL: equ 0
	OutputStr: db "%2d.line: %s",0
	ErrArg: db "Error: missing argument (filename)",10,0
	PermStr: db 'r',0
	ErrFile: db "Error:Unable to open file",10,0
	ErrClose: db "Error:Unable to close file",10,0
	
section .bss
	FileToOpen: resb 32
	LineStr: resb MAXLINE
	NrArgs: resd 1
	FILEhd: resd 1

section .text

GLOBAL main
EXTERN fopen			;FILE *fopen(const char *filename, const char *mode)
EXTERN fclose			;int fclose(FILE *stream)
EXTERN fgets			;char *fgets(char *str, int n, FILE *stream)
EXTERN fprintf   		;int fprintf(FILE *stream, const char *format, ...)
;EXTERN fgetc			;int fgetc(FILE *stream)

EXTERN stdout
EXTERN EOF			;EOF is negative integer

main:
	push ebp
	mov ebp,esp
	push ebx
	push edi
	push esi

;check the argument of the program and store it in FileToOpen	

	mov esi,DWORD[ebp+8]
	mov DWORD[NrArgs],esi

;check if the argument s present
	cmp esi,0x02
	jb .error_arg
;get the filename string to FileToOpen
	mov esi,DWORD[ebp+12]
	mov esi,DWORD[esi+4]		;address of the argument string
	mov edi, FileToOpen
	.loop:
	movsb
	mov ecx,DWORD[edi-1]
	cmp ecx,NULL
	jnz .loop

;open file for reading
	push PermStr
	push FileToOpen
	call fopen
	add esp,0x08
	cmp eax,0x00
	jz .error_fileopen
	mov DWORD[FILEhd],eax	;stores a pointer to *FILE (open file), handler is also stored in esi
	mov esi,eax
	

;loop through the lines using fgets, reading each line to LineStr
	mov ebx,0x01			;setup the line counter in sacred register
	.loop2:
	push esi
	push MAXLINE
	push LineStr
	call fgets			;we get pointer to read line in eax
	add esp,0x0c
	cmp eax,0x00			;if EOF then eax is 0
	jz .endOfRead

;add line number to LineStr and printf the line to stdout
	push eax
	push ebx
	push OutputStr
	push DWORD[stdout]
	call fprintf
	add esp,0x10
	inc ebx
	jmp .loop2

;close the file when reaching EOL

.endOfRead:
	push esi
	call fclose
	add esp,0x04
	cmp eax,0x00
	jl .error_fileclose
	
	jmp Ex

.error_fileclose:
	push ErrClose
	push DWORD[stdout]
	call fprintf
	add esp,0x08
	jmp Ex


.error_arg:
	push ErrArg
	push DWORD [stdout]
	call fprintf
	add esp,0x08
	jmp Ex

.error_fileopen:
	push ErrFile
	push DWORD[stdout]
	call fprintf
	add esp,0x08
	jmp Ex


Ex:
	pop esi
	pop edi
	pop ebx
	mov esp,ebp
	pop ebp
	ret
