/*
* Darius Jones
* Lab 8 Task 3
* 3/15/2018
*/

#ifndef table_h
#define table_h
#include <time.h>
#define ERROR -1


struct entry{
	int pid;
	int page;
	struct tm time_stamp;
};

struct inverted_ptable {
	
	int page_size;
	int number_of_pages;
	struct entry *table[];

};


void initInverted(struct inverted_ptable **inverted_table, int memory_size, int frame_size);
int translate(struct inverted_ptable *inverted_table, int pid, int page, int offset);
void releaseInverted(struct inverted_ptable **inverted_table);
int tableSearch(struct inverted_ptable *inverted_table, int pid, int page);
int findOldIndex(struct inverted_ptable *inverted_table, int pid, int page);
void display(struct inverted_ptable *inverted_table) ;



#endif