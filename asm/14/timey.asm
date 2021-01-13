
section .data
	Epoch: db "Seconds since epoch :%d",10,0
	Epoch_len: equ $-Epoch
	TextTime: db "Current time and date :%s",10,0
	TextTime_len: equ $-TextTime
	Seconds: db "Seconds :%d",10,0
	Seconds_len: equ $-Seconds
	Minutes: db "Minutes :%d",10,0
	Minutes_len: equ $-Minutes
	Hours: db "Hours :%d",10,0
	Hours_len: equ $-Hours
	Days:db "Day :%d",10,0
	Days_len: equ $-Days
	Months: db "Months :%d",10,0
	Months_len: equ $-Months
	Years: db "Years :%d",10,0
	Years_len: equ $-Years
	All: db "Current time and date : %d:%d:%d  %d.%d.%d",10,0
	All_len: equ $-All

	


section .bss
	OldTime: resd 1
	NewTime: resd 1
	Tm: resd 9

section .text

%macro MPrintf 2
	push %1
	push %2
	call printf
	add esp, 0x08
%endmacro


EXTERN time
EXTERN ctime
EXTERN localtime
EXTERN printf

GLOBAL main


main:
	push ebp
	mov ebp,esp
	push ebx
	push esi
	push edi

	push 0x00
	call time
	add esp,0x04
	mov dword[OldTime],eax

	MPrintf eax, Epoch
	
	push OldTime
	call ctime
	add esp,0x04
	
	
	MPrintf eax,TextTime

	push OldTime
	call localtime
	add esp,0x04

	mov esi,eax
	mov ecx,9
	mov edi,Tm
	rep movsd

	MPrintf dword[Tm+0],Seconds
	MPrintf dword[Tm+4],Minutes
	MPrintf dword[Tm+8],Hours
	MPrintf dword[Tm+12],Days
	MPrintf dword[Tm+16],Months
	MPrintf dword[Tm+20],Years	

	add dword[Tm+20],1900
	add dword[Tm+16],0x01

	push dword[Tm+20]
	push dword[Tm+16]
	push dword[Tm+12]
	push dword[Tm+0]
	push dword[Tm+4]
	push dword[Tm+8]
	push All
	call printf
	add esp,28


	pop edi
	pop esi
	pop ebx
	mov esp,ebp
	pop ebp
	ret
