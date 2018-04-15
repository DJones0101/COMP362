/*
* Darius Jones
* Project 1 task 1
* 4/5/2018
*/

#include "filesystem.h"

int main(int argc, char *argv[]) {	

	file_system_create();
	printf("-------------------------------directory_create(), file_create()\n");
	directory_create(memory[0], "/sub_dir");
	file_create(memory[2],"info.txt");
	display_bitvector();

	printf("-------------------------------After file_delete()\n");

	file_delete(memory[2],"info.txt");
	display_bitvector();
	file_create(memory[2],"info.txt");
	printf("-------------------------------file_create() again \n");
	display_bitvector();
	printf("-------------------------------directory_delete() with a file inside it \n");

	free_system();
	return 0;
}