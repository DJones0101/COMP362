# Usage :
# [make] -> compiles
# [make run ]-> runs the exe
# [make clean] -> removes the exe

all: filesystem.c 
	gcc -g -Wall -o filesystem filesystem.c main.c filesystem.h

clean: 
	$(RM) filesystem

run: filesystem
	./filesystem 