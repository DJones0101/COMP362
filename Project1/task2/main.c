/*
* Darius Jones
* Project 1 task 2
* 4/15/2018
*/

#include "filesystem.h"

int main(int argc, char *argv[]) {

	file_system_create();
	
	file_create(memory[0], "file");
	open_file(memory[0], "file", WRITE_PERMISSION);
	write_file("HELLO WORLD",  "file");
	close_file("file");
	open_file(memory[0], "file", READ_PERMISSION);

	char *test = malloc(11);
	strcpy(test, read_file("file"));
	printf("%s\n",test);


		
	free_system();
	return 0;
}