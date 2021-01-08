# usage:
# make  # compile and link all .asm files
# make clean # remove all .o and elf files


.PHONY =  termo1 clean

COMPILER = nasm
COMPILERFLAG = -g -f elf32 -F stabs
COMPILERFLAG_nodbg = -f elf32
LINKER = ld
LINKERFLAG = -m elf_i386

SRCS = $(wildcard *.asm)
OBJECTS = $(SRCS:%.asm= %.o)

termo1: ${OBJECTS}
	${LINKER} ${LINKERFLAG} *.o -o $@  

%.o: %.asm
	${COMPILER} ${COMPILERFLAG} $<


clean:
	rm -rvf *.o termo1 nodbg

