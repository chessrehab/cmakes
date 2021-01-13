# usage:
# make  # compile and link all .asm files
# make clean # remove all .o and elf files


.PHONY =  timey clean

COMPILER = nasm
COMPILERFLAG = -g -f elf32 -F stabs
COMPILERFLAG_nodbg = -f elf32
LINKER = gcc
LINKERFLAG = -m32

SRCS = $(wildcard *.asm)
OBJECTS = $(SRCS:%.asm= %.o)

timey: ${OBJECTS}
	${LINKER} ${LINKERFLAG} *.o -o $@  

%.o: %.asm
	${COMPILER} ${COMPILERFLAG} $<


clean:
	rm -rvf *.o timey nodbg

