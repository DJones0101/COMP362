/*
* Darius Jones
* Project 1 task 2
* 4/15/2018
*/

#include "filesystem.h"

int main(int argc, char *argv[]) {

	printf("new filesystem (superblock and it's index_nd)\n");
	file_system_create();
	display_bitvector();
	directory_create(memory[0], "/sub");
	printf("------------------------------created a new directory within the superblock\n");
	display_bitvector();
	printf("------------------------------created a new file within the new directory\n");
	file_create(memory[2], "file.txt");
	display_bitvector();
	printf("------------------------------deleted the file\n");
	file_delete(memory[2], "file.txt");
	display_bitvector();
	printf("------------------------------created a new file within the new directory\n");
	file_create(memory[2], "file.txt");
	display_bitvector();
	printf("------------------------------deleted the directory with the file in it\n");
	directory_delete(memory[2],memory[0]);
	display_bitvector();
	printf("------------------------------created a new file within the  superblock\n");
	file_create(memory[0], "file.txt");
	display_bitvector();
	file_delete(memory[2], "file.txt");
	printf("------------------------------deleted the file in the superblock\n");
	display_bitvector();


	free_system();
	return 0;
}