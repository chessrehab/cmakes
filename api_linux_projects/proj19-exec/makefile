# usage:
# make		 # compile all binary
# make clean	 # remove ALL binary and object files


.PHONY = exec01 clean

COMPILER = gcc 
LINKERFLAG = -lm

SRCS := $(wildcard  *.c)
OBJECTS := $(SRCS:%.c= %.o)



exec01:${OBJECTS}
	@echo "Linking object files to executable..." 
	${COMPILER} ${LINKERFLAG} *.o -o $@

%.o: %.c
	@echo "Compiling source code to object files..."
	${COMPILER} -c $<



clean: 
	@echo "Cleaning all object files and executables, leaving the source code.."
	rm -rvf *.o ${BINS} exec01





