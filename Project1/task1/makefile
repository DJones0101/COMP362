# https://stackoverflow.com/questions/1484817/how-do-i-make-a-simple-makefile-for-gcc-on-linux
CC=gcc 
CFLAGS= -g -Wall

all: filesystem
filesystem: filesystem.o
filesystem.o: filesystem.c filesystem.h 

clean:
	rm -f filesystem filesystem.o
run: filesystem
	./filesystem