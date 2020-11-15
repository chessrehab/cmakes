
; nasm -f elf -F stabs -g prog01.asm
; ld -o sndbx prog01.o ;doesnt work on 64bit architecture, can be used for 32bit processor
; ld -m elf_i386 -s -o sndbx prog01.o ;works on 64bit architecture




section .data                               ;initialized global variables area
    otpt db "Hello Martin", 10              ;definition of a string, with pointer otpt pointing to first byte
    otpt_len equ $-otpt                     ;definition of a constant for string length calculated from the memory pointer minus first byte of string
    

section .bss                                ;uninitialized global variables area

section .text                               ;text of code area
    global _start                           ;entry point defining label entry point of code
    
    
_start:                                     ;label entry point
    nop                                     ;no operation, point for debugger to stop
    
    mov eax,04h                             ;move code for output(4) linux api system call into eax register
    mov ebx,01h                             ;move fd number for stdout operation to eax register
    mov ecx,otpt                            ;move a pointer to first char byte for stdout into ecx register
    mov edx,otpt_len                        ;move a string length variable to edx register
    int 080h                                ;call linux system call (software interrupt)
    
    nop                                     ;no operation, point for debugger to stop

_exit:
    mov eax,1                               ;move code for exit(1) linux system call into eax register
    mov ebx,0                               ;move program return value to register ebx
    int 80h                                 ;call linux api system call(software interrupt)
    


 
