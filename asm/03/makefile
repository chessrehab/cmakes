# usage:
# make  # compile and link all .asm files
# make clean # remove all .o and elf files


.PHONY =  ucaser clean

COMPILER = nasm
COMPILERFLAG = -g -f elf32 -F stabs
LINKER = ld
LINKERFLAG = -m elf_i386

SRCS = $(wildcard *.asm)
OBJECTS = $(SRCS:%.asm= %.o)

ucaser: ${OBJECTS}
	${LINKER} ${LINKERFLAG} $< -o $@  

%.o: %.asm
	${COMPILER} ${COMPILERFLAG} $<


clean:
	rm -rvf *.o sndbx

