/*
* Darius Jones
* Lab 8 Task 3
* 3/15/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inverted.h"


/*
* allocates and initializes the table for the given sizes of the memory and frame
* to ensure that the library is thread-safe, the table should be a struct that
* includes metadata such as page size and the number of pages along the translation
* table (that can be a 2-dimensional array, or a one-dimensional array of structs)
*/

void initInverted(struct inverted_ptable **inverted_table, int memory_size, int frame_size) {

	*inverted_table = (struct inverted_ptable*)malloc(sizeof(struct inverted_ptable));
	(*inverted_table)->page_size = (memory_size / frame_size);
	(*inverted_table)->number_of_pages = frame_size;



	int count;
	for (count = 0; count < frame_size; count++) {

		(*inverted_table)->table[count] = (struct entry*)malloc(sizeof(struct entry));

	}

}


/*
* translates a logical address <pid, page, offset> into a physical address
* if the address is invlid it returns -1
* if there is no entry for the pid and the page number in the table, it has to be added
* if there is no room in the table for the new entry, then the oldest entry has to be removed
*/
int translate(struct inverted_ptable *inverted_table, int pid, int page, int offset) {


	int frame_index = tableSearch(inverted_table, pid, page);
	int page_size = inverted_table->page_size;

	if (frame_index != ERROR) {// request found, frame_index equal to where it was found

		inverted_table->table[frame_index]->pid = pid;

		inverted_table->table[frame_index]->page = page;

	} else if (frame_index == ERROR) {// request not found, search table for oldest time

		int empty_frame_found = findEmpty(inverted_table, pid, page);

		if (empty_frame_found != ERROR) { // empty frame found, frame_index is equal to where it was found

			frame_index = empty_frame_found;
			inverted_table->table[frame_index]->pid = pid;
			inverted_table->table[frame_index]->page = page;
		
			

		} else { // not empty frame found so find the oldest one

			frame_index = findOldIndex(inverted_table, pid, page);
			inverted_table->table[frame_index]->pid = pid;
			inverted_table->table[frame_index]->page = page;
			
			
		}

	}

	return (frame_index * page_size) + offset;

}


/*
* releases the inverted table and sets the reference to NULL
*/
void releaseInverted(struct inverted_ptable **inverted_table) {

	int index;
	int number_of_pages = (*inverted_table)->number_of_pages;

	for (index = 0; index < number_of_pages; index++) {

		free((*inverted_table)->table[index]);
	}

	inverted_table = NULL;
}


int tableSearch(struct inverted_ptable *inverted_table, int pid, int page) {

	int index;
	for (index = 0; index < inverted_table->number_of_pages; index++) {

		if (inverted_table->table[index]->pid == pid && inverted_table->table[index]->page == page ) {
			inverted_table->table[index]->time_stamp = time(NULL);
			return index;
		}
	}
	return ERROR;
}

int findOldIndex(struct inverted_ptable *inverted_table, int pid, int page) {

	int index;
	int max_index;
	time_t current_max_time = time(NULL);
	int number_of_pages = inverted_table->number_of_pages;
	time_t current_time_stamp;
	// return the index of the one with the largest

	for (index = 0; index < number_of_pages; index++) {

		current_time_stamp = inverted_table->table[index]->time_stamp;

		if (difftime(current_time_stamp, current_max_time) > 0) {
			max_index = index;
			inverted_table->table[max_index]->time_stamp = time(NULL);
			current_max_time = current_time_stamp;
		}

	}

	return max_index;
}

int findEmpty(struct inverted_ptable *inverted_table, int pid, int page) {

	int number_of_pages = inverted_table->number_of_pages;
	int index;

	for (index = 0; index < number_of_pages; index++) {

		if (inverted_table->table[index]->pid == 0 ) {

			return index;
		}


	}

	return ERROR;

}

void display(struct inverted_ptable *inverted_table) {

	int index;
	int number_of_pages = inverted_table->number_of_pages;
	char page[] = "Page";
	char pid[] = "Pid";
	printf("\n");
	printf("\t%-12s%-12s\n", pid, page);

	for (index = 0; index < number_of_pages; index++) {

		printf("\t%-12d%-12d\n", inverted_table->table[index]->pid, inverted_table->table[index]->page);

	}
	printf("\n");

}