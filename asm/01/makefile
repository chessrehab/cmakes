sndbx: prog01.o
	ld -m elf_i386 -o sndbx prog01.o
prog01.o: prog01.asm
	nasm -f elf -F stabs -g prog01.asm

