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

	struct inverted_ptable **inverted = malloc(sizeof(struct inverted_ptable*));
	**inverted = **inverted_table;
	(*inverted)->page_size = (memory_size / frame_size);
	(*inverted)->number_of_pages = frame_size;

	int count;
	for (count = 0; count < frame_size; count++) {

		(*inverted)->table[count] = malloc(sizeof(struct entry*));
	}



}


/*
* translates a logical address <pid, page, offset> into a physical address
* if the address is invlid it returns -1
* if there is no entry for the pid and the page number in the table, it has to be added
* if there is no room in the table for the new entry, then the oldest entry has to be removed
*/
int translate(struct inverted_ptable *inverted_table, int pid, int page, int offset) {


	// the frame is the struct within the table struct

	int physical_address = (pid * inverted_ptable->page_size) + offset;

	if (found) {

		frame_index = where it was found;

	} else if (not found) {

		tableSearch for empty frame;

	if ( empyt frame found) { frame_index = where it was found}

	} else if ( no empty space) {
		find oldest entry in the frame and insert neew one there.
	}

	return physical_address;

}


/*
* releases the inverted table and sets the reference to NULL
*/
void releaseInverted(struct inverted_ptable **inverted_table) {

}


int tableSearch(struct inverted_ptable *inverted_table, int pid, int page) {

	int index;
	bool is_found;

	for (index = 0; index < inverted_ptable->number_of_pages; index++) {

		if (inverted_ptable->table[index]->pid == pid && inverted_ptable->table[index]->page == page ) {

			is_found = true;
			break;

		} else {

			is_found = false;
			break;
		}
	}

	return index;

}

int findOldIndex(struct inverted_ptable *inverted_table, int pid, int page) {

}

void display(struct inverted_ptable *inverted_ptable) {

}