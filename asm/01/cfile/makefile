# usage:
# make  # compile and link all .c files
# make clean # remove all .o and elf files


.PHONY =  sndbx clean

COMPILER = gcc
COMPILERFLAG = -g -c 
LINKER = gcc
LINKERFLAG = 

SRCS = $(wildcard *.c)
OBJECTS = $(SRCS:%.c= %.o)

csndbx: ${OBJECTS}
	${LINKER} ${LINKERFLAG} $< -o $@  

%.o: %.c
	${COMPILER} ${COMPILERFLAG} $<


clean:
	rm -rvf *.o csndbx

