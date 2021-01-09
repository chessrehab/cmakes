# usage:
# make  # compile and link all .asm files
# make clean # remove all .o and elf files


.PHONY =  videobuf clean

COMPILER = nasm
COMPILERFLAG = -g -f elf32 -F stabs
COMPILERFLAG_nodbg = -f elf32
LINKER = ld
LINKERFLAG = -m elf_i386

SRCS = $(wildcard *.asm)
OBJECTS = $(SRCS:%.asm= %.o)

videobuf: ${OBJECTS}
	${LINKER} ${LINKERFLAG} *.o -o $@  

%.o: %.asm
	${COMPILER} ${COMPILERFLAG} $<


clean:
	rm -rvf *.o videobuf nodbg

