/*
* Darius Jones
* Lab 8 Task 3
* 3/15/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inverted.h"

#define MEMORY_SIZE 20
#define PAGE_SIZE 4

int main(int argc, char *argv[]) {

	struct inverted_ptable *table;
	initInverted(&table, MEMORY_SIZE, PAGE_SIZE);
	printf("Page size: %d\n", table->page_size);
	printf("Number of Pages: %d\n", table->number_of_pages);


	srand(time(NULL));
	int random_pid;
	int random_offset;
	int random_page;
	int count = 0;
	int physical_address;

	/*Write a test program that generates random addresses
	(i.e., <pid, page, offset>) and uses the library to translate them into physical equivalents.*/


	//while (true) {


	//	if (count == PAGE_SIZE) {break;}
		
	//	printf("Logical Address is (%d,%d,%d)\n", random_pid, random_page, random_offset);
	//	physical_address = translate(table, random_pid, random_page, random_offset);
		display(table);
	//	printf("Physical Address is %d\n", physical_address);
	//	count++;

	//}



	releaseInverted(&table);

	return 0;

}






