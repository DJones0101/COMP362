/*
* Darius Jones
* Project 1 task 2
* 4/15/2018
*/

#include "filesystem.h"

int main(int argc, char *argv[]) {

	file_system_create();
	printf("-----------------created the filesystem\n");
	file_create(memory[0],"fio");
	display_bitvector();
	
	printf("Global table : %d\n", numOfEntries_global);
	printf("-----------------opened the file wrote to it and read it\n");

	open_file(memory[0],"fio",WRITE_PERMISSION);
	write_file("HELLO WORLD", "fio");
	close_file("fio");

	//display_bitvector();
	printf("Global table : %d\n", numOfEntries_global);
	open_file(memory[0],"fio",READ_PERMISSION);
	read_file("fio");


	printf("-----------------closed the file\n");

	close_file("fio");
	printf("Global table : %d\n", numOfEntries_global);
	



	free_system();
	return 0;
}