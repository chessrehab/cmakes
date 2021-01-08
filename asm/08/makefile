# usage:
# make  # compile and link all .asm files
# make clean # remove all .o and elf files


.PHONY =  termacro clean

COMPILER = nasm
COMPILERFLAG = -g -f elf32 -F stabs
COMPILERFLAG_nodbg = -f elf32
LINKER = ld
LINKERFLAG = -m elf_i386

SRCS = $(wildcard *.asm)
OBJECTS = $(SRCS:%.asm= %.o)

termacro: ${OBJECTS}
	${LINKER} ${LINKERFLAG} *.o -o $@  

%.o: %.asm
	${COMPILER} ${COMPILERFLAG} $<


clean:
	rm -rvf *.o termacro nodbg

