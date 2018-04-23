/*
* Darius Jones
* Project 1 task 2
* 4/15/2018
*/

#include "filesystem.h"

int main(int argc, char *argv[]) {

	file_system_create();
	directory_create(memory[0], "1sssub");
	file_create(memory[0],"fio");
	open_file(memory[0],"fio",WRITE_PERMISSION);
	write_file("HELLO WORLD", "fio");
	printf("GLOBAL TABLE SIZE %d\n", numOfEntries_global );
	display_bitvector();
	read_file("fio");
	



	free_system();
	return 0;
}