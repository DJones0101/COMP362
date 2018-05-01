# Darius Jones

all: disk.c 
	gcc -g -Wall *.c disk.h -o disk -lm -lrt 

clean: 
	$(RM) disk
	$(RM) core
	#$(RM) timer
	clear

run: disk
	./disk

debug:
	gdb disk core

