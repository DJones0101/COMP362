/*
* Darius Jones
* Lab 8 Task 3
* 3/15/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <table.h>



/*
* allocates and initializes the table for the given sizes of the memory and frame
* to ensure that the library is thread-safe, the table should be a struct that
* includes metadata such as page size and the number of pages along the translation
* table (that can be a 2-dimensional array, or a one-dimensional array of structs)
*/

void initInverted(struct Page_Table **inverted_table, int memory_size, int frame_size){

	

}


/*
* translates a logical address <pid, page, offset> into a physical address
* if the address is invlid it returns -1
* if there is no entry for the pid and the page number in the table, it has to be added
* if there is no room in the table for the new entry, then the oldest entry has to be removed
*/
int translate(struct Page_Table *inverted_table, int pid, int page, int offset){

	/*

	

	return (frame_size * page_size) + offset;


	*/

}


/*
* releases the inverted table and sets the reference to NULL
*/
void releaseInverted(struct Page_Table **inverted_table){

}