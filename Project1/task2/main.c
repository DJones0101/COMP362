/*
* Darius Jones
* Project 1 task 2
* 4/15/2018
*/

#include "filesystem.h"

int main(int argc, char *argv[]) {

	file_system_create();
	display_bitvector();
	directory_create(memory[0], "/sub");
	file_create(memory[2], "file.txt");
	open_file(memory[2], "file.txt", WRITE_PERMISSION);
	display_bitvector();

	char what_to_write[10] = "wzaty8SQqu";

	write_file(what_to_write, "file.txt");
	close_file("file.txt");
	display_bitvector();
	display_table_global();
	open_file(memory[2], "file.txt", READ_PERMISSION);
	read_file("file.txt");
	close_file("file.txt");



	free_system();
	return 0;
}