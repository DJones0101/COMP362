/*
* Darius Jones
* Lab 8 Task 3
* 3/15/2018
*/

#ifndef _table_h_
#define _table_h_

#define MAX_SIZE 10

struct Translate_Table{};

struct Page_Table{
	int page_size;
	int  number_of_pages;
	struct Translate_Table translate[MAX_SIZE]; 
};


void initInverted(struct Page_Table **inverted_table, int memory_size, int frame_size);
int translate(struct Page_Table *inverted_table, int pid, int page, int offset);
void releaseInverted(struct Page_Table **inverted_table);


#endif