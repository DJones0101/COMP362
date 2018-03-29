/*
* Darius Jones
* Lab 9 Task 2
* 3/29/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {HIT = 0, FAULT_SPACE, FAULT_NO_SPACE};

typedef struct {
	int data;
	NODE *next;
	NODE *prev;
} NODE;

int maximum_capacity;
int current_capacity;
int page_fault_count;


void remove_last_node(/**/);
void replace_head_node(/**/);
void swap_node(/**/);

// int search_list(/**/); search list for
// void create_list(/**/); maybe
// void 

int main(int argc, char *argv[]) {

	return 0;
}



/*
int search_list(???){

	
	int status;

	while( current node != NULL){
		

		if (current.data ==  ){  found

			status = HIT;
			break;

		}

		traverse list

	}

	if( found == fales &&  currnent_capacity == maximum_capacity){

		status = FAULT_NO_SPACE;
		page_fault_count++;

	} else if(found == fales &&  currnent_capacity < maximum_capacity){

		status = FAULT_SPACE;
		page_fault_count++;
	
	}
	
	
	return status;

}
*/
