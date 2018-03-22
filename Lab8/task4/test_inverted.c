/*
* Darius Jones
* Lab 8 Task 3
* 3/21/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inverted.h"



int main(int argc, char *argv[]) {

	struct inverted_ptable *table;
	initInverted(&table, MEMORY_SIZE, PAGE_SIZE);


	srand(time(NULL));
	int random_pid;
	int random_offset;
	int random_page;
	int count = 0;
	int physical_address;
	int option;

	/*Write a test program that generates random addresses
	(i.e., <pid, page, offset>) and uses the library to translate them into physical equivalents.*/
	printf("-----Empty table created-----\n");
	display(table);
	printf("------------------------------\n");
	

	while (true) {

		printf("Press 1 to generate a address or 2 to quit\n");
		fscanf(stdin,"%d",&option);
		if(option == 2){printf("Quitting program\n"); exit(EXIT_SUCCESS);}

		

		if(option == 1){
			
			random_pid = (rand() % 4) + 1;
			random_offset = rand() % 4;
			random_page = rand() % 4;
			physical_address = translate(table, random_pid, random_page, random_offset);
			printf("Logical Address generated (pid: %d,page: %d,offset: %d)\n", random_pid, random_page, random_offset);
			printf("Translated to Physical Address %d\n", physical_address);
			display(table);
			printf("------------------------------\n");
		
		}
	
	}



	releaseInverted(&table);

	return 0;

}






