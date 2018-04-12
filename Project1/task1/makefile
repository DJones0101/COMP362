# Usage :
# make or make all -> compiles
# make run -> runs the exe
# clean removes the exe

all: filesystem.c 
	gcc -g -Wall -o filesystem filesystem.c main.c headers.h

clean: 
	$(RM) filesystem

run: filesystem
	./filesystem 