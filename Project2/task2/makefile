# Darius Jones

all: disk.c 
	gcc -g -Wall *.c disk.h -o disk -lm

clean: 
	$(RM) disk
	$(RM) core
	clear

run: disk
	./disk

debug:
	gdb disk core

