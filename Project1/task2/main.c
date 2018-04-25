/*
* Darius Jones
* Project 1 task 2
* 4/15/2018
*/

#include "filesystem.h"

int main(int argc, char *argv[]) {


	char buffer[50];
	file_system_create();
	
	file_create(memory[0], "file");
	open_file(memory[0], "file"/*, WRITE_PERMISSION*/);
	write_file("HELLO WORLD---PLEASE WORK!!!\0",  "file");
	close_file("file");
	open_file(memory[0], "file"/*, READ_PERMISSION*/);

	read_file("file", buffer);

	printf("%s\n",buffer );


		
	free_system();
	return 0;
}