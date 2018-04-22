/*
* Darius Jones
* Project 1 task 2
* 4/15/2018
*/

#include "filesystem.h"

int main(int argc, char *argv[]) {

	file_system_create();

	directory_create(memory[0], "/sub");
	file_create(memory[2], "file.txt");
	open_file(memory[2],"file.txt", WRITE_PERMISSION);

	char *what_to_write = "wzaty8SQqu";

	write_file(what_to_write, "file.txt");
	read_file("file.txt");
	close_file("file.txt");



	free_system();
	return 0;
}