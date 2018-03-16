/*
* Darius Jones
* Lab 8 Task 3
* 3/15/2018
*/

#ifndef _table_h_
#define _table_h_

#define MAX_SIZE 10

struct Table_Item{
	int pid;
	int page_number;
	int time_stamp;
};

struct Page_Table{
	int page_size;
	int  number_of_pages;
	srtuct Table_Item item[MAX_SIZE];
};


void initInverted(struct Page_Table **inverted_table, int memory_size, int frame_size);
int translate(struct Page_Table *inverted_table, int pid, int page, int offset);
void releaseInverted(struct Page_Table **inverted_table);


#endif