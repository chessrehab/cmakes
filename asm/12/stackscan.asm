
section  .data
	ExitMsg: db 10,"..exited gracefully...",10
	ExitMsg_len: equ $-ExitMsg
	
	ArgLabel: db 10,"X.argument:"
	ArgLabel_len: equ $-ArgLabel

	MAXVARS: equ 255
	MAXARGS: equ 0x0a

	MAXSEARCH: equ  0xff

	
	VarLabel: db 10,"XX.variable:"
	VarLabel_len: equ $-VarLabel

section .bss

	ArgCount: resb 1
	ArgPtrs: resd MAXARGS
	ArgLens: resb MAXARGS
	VarStart: resd 1
	VarCount: resb 1
	VarPtrs: resd MAXVARS
	VarLens: resb MAXVARS
	ReadChar: resb 1

section .text

GLOBAL _start

PrintArgs:
;INPUT:esi=address of the string to be printed, edi=length of the string to be printed, ebp=argument number
;OUTPUT:nothing
;MODIFIES:
;CALLS:

	pushad				;backup registers

	add ebp,0x30			;
	mov edx,ebp
	mov byte[ArgLabel+1],dl

	mov eax,0x04
	mov ebx,0x01
	mov ecx,ArgLabel
	mov edx,ArgLabel_len
	int 0x80

	mov eax,0x04
	mov ecx,esi
	mov edx,edi
	int 0x80

	mov eax,0x04
	mov ecx,0x0a
	mov edx,1
	int 0x80

	popad

	ret

PrintVars:
;INPUT:ESI=address of the string to be printed, EDI=length of the string to be printed, EBP=variable number
;OUTPUT:nothing
;MODIFIES:
;CALLS:

	pushad				;backup registers

	mov eax,ebp			;move cycle number to eax
	inc eax				;increase eax by one
	mov ch,0x0a			;move divisor 10 to ch
	div ch				;divide ax (cycle number) by 10
	add al,0x30			;add ascii offest to al
	add ah,0x30			;add ascii offset to ah
	mov word[VarLabel+1],ax		;move ascii digits of cycle number to Variable label
	

	mov eax,0x04			;system call for sys write
	mov ebx,0x01			;standard output
	mov ecx,VarLabel		;Var label string address
	mov edx,VarLabel_len		;Var label len
	int 0x80			;print out var label

	mov eax,0x04			;system call sys wrrite
	mov ecx,dword[VarPtrs+ebp*4]			
	movzx edx,byte[VarLens+ebp]
	int 0x80

	mov eax,0x04
	mov ecx,0x0a
	mov edx,1
	int 0x80

	popad

	ret


_start:
	nop

	mov edx,dword[esp]		;we have number of arguments in edx, esp moves one up
	mov byte[ArgCount],dl		;we put number of arguments to ARgCount
	mov ecx,edx			;duplicate number of args in ecs
	shl ecx,2			;multiply number of args in ecx *4
	lea edi, [esp+ecx+8]		;put address of start of variable addresse in edi
	mov dword[VarStart],edi		;save the stack address of var pointers start in VarStart
	mov esi,[edi]			;put the address of first var in esi
	mov dword[VarPtrs],esi		;put the address of first var in VarPtrs
	mov esi,edi			;duplicate address of var addr start in esi
	mov ecx, MAXVARS		;put max scan number in ecx
	mov eax,0x00			;put search 4b 0 in eax
	repne scasd			;scan double words till doubleword 0 is found
	sub edi,4			;step 4 bytes back in edi
	sub edi,esi			;calculate differsence between start of var adreses and end of var addresse
	shr edi,2			;calculate abs number of doubles=number of vars
	mov eax,edi			;put number of vars to eax
	mov byte[VarCount],al		;store nmber of vars in VarCount

	xor ebp,ebp			;put ebp to 0
	movzx edx,byte[VarCount]	;put number of vars in edx

	.readVars:
	mov al,0x00			;put search string in al
	mov ecx,dword[VarStart]
	lea esi,[ecx+ebp*4]	;put address of variable address from the stack to esi
	mov ecx,[esi]			;put address of the variable to ecx
	mov dword[VarPtrs+ebp*4],ecx	;put pointer to variable to Var pointer in memory
	mov edi,ecx			;put the pointer to variable to edi		;
	mov esi,edi			;duplicate the starting byte of var to esi
	mov ecx,MAXSEARCH
	repne scasb			;serch for search string (0x00000000)
	dec edi				;step 1 back
	sub edi,esi			;calculate length
	mov eax,edi			;move lenght to eax
	mov byte[VarLens+ebp],al	;store length in VarLens

	call PrintVars

	inc ebp
	dec edx
	jnz .readVars

	xor ebp,ebp
	mov edx,dword[ArgCount]
	.readArgs:
	mov edi,dword[esp+ebp*4+4]
	mov dword[ArgPtrs+ebp*4],edi
	mov esi,edi
	mov eax, 0x00
	mov ecx, MAXSEARCH
	repne scasb
	dec edi
	sub edi,esi
	mov eax,edi
	mov byte[ArgLens+ebp], al
	call PrintArgs
	inc ebp
	dec edx
	jnz .readArgs



	jmp Ex
	nop
Ex:
	mov eax,0x03
	mov ebx,0x00
	mov ecx,ReadChar
	mov edx, 1
	int 0x80


	mov eax, 0x4
	mov ebx, 0x1
	mov ecx, ExitMsg
	mov edx, ExitMsg_len
	int 0x80

	mov eax, 0x1
	mov ebx, 0x0
	int 0x80


