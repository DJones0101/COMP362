# Usage :
# [make] -> compiles
# [make run ]-> runs the exe
# [make clean] -> removes the exe

all: disk.c 
	gcc -g -Wall disk.c disk.h -o disk

clean: 
	$(RM) disk

run: disk
	./disk 