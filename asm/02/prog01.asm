
; nasm -f elf -F stabs -g prog01.asm
; ld -o sndbx prog01.o ;doesnt work on 64bit architecture, can be used for 32bit processor
; ld -m elf_i386 -s -o sndbx prog01.o ;works on 64bit architecture
; usage sndbx >outputfile <inputfile



section .data                               ;initialized global variables area
    otpt: db " 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00","| xxxxxxxxxxxxxxxx", 10              ;definition of a string, with pointer otpt pointing to first byte where the line of output will be genrated
    LEN1: equ $-otpt
    OFFS equ 50
    OTPT_LEN equ 16                 ;storing the lenghth of the line in muber of digits
    lkp db "0123456789abcdef"               ;lookup table for hex digits
    
section .bss                                ;uninitialized global variables area
    buff resb 16                              ;empty buffer for reading number of chars from buffer

section .text                               ;text of code area
    global _start                           ;entry point defining label entry point of code
        
_start:                                     ;label entry point
    nop                                     ;no operation, point for debugger to stop

_read_op:                                   ;label entry point for reading from file operation
    mov eax,3                               ;move code for input(3) linux api system call into eax register
    mov ebx,0                               ;move fd number for stdinput operation to eax register
    mov ecx,buff                            ;move a pointer to first char byte of predefined uninitialized buffer
    mov edx,OTPT_LEN                            ;number of chars to be read stored in edx register
    int 80h                                ;call linux system call (software interrupt)
    
    mov ebp,eax
    dec ebp                             ;return value of read syscall is stored in eax. we duplicate ot to ebp for later
    cmp eax,0                               ;testing if return value was 0
    je _finish                              ;if equal then reading reached file end and jumps to label _finish
    
    xor ecx,ecx                             ;wiping out ecx register
    
_scan_op:                                   ;lable for entry of buffer scanning operation
    xor eax,eax
    mov ebx,ecx                             ;copy counter register ecx to ebx
    shl ebx,1                               ;multiply ebx by 2
    add ebx,ecx                             ;add one more multiplication to ebx= overall echieves ebx=ecx * 3
    
    mov al,byte [buff+ecx]                   ;copies one char from read buffer to al register
    mov dl,al  
    cmp al,64
    jna __low
    cmp al,122
    ja __low
    mov [otpt+ecx+OFFS],al
    jmp __cnt
__low:
    mov [otpt+ecx+OFFS],byte 46
    jmp __cnt

__cnt:

 
    and al,0fh                     ;masks out higher 4 bits in 8bit al register
    mov al,[lkp+eax]                   ;makes a lookup in lkp to the position of the hex value and moves the digit byte to di
    mov [otpt+ebx+2],al                   ;move the hex char to right place in final row
    
    shr dl,4                                ;moves 4 higher bits in dl register right and wipes out lower 4 bits
    mov dl,[lkp+edx]                   ;makes a lookup in lkp to the position of the hex value and moves the digit byte to di
    mov [otpt+ebx+1],dl                   ;
    
    inc ecx
    cmp ecx,ebp                         ;compares counter in ecx whether it reached the end of scanned buffer
    jna _scan_op
    
_write_op:
    mov eax,4                               ;set up eax register to number of linux api write system call
    mov ebx,1                               ;set up ebx register to number of output file descriptor
    mov ecx,otpt                      ;set the ecx register to point to firts byte of the prepared string
    mov edx,LEN1                             ;set the edx register to number of bytes to be written
    int 80h                                 ;execute write system call

    jmp _read_op
    

_finish:
    mov eax,1                               ;move code for exit(1) linux system call into eax register
    mov ebx,0                               ;move program return value to register ebx
    int 80h                                 ;call linux api system call(software interrupt)
    
    nop

 
