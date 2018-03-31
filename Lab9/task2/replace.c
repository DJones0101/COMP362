/*
* Darius Jones
* Lab 9 Task 2
* 3/29/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {HIT = 0, FAULT_SPACE, FAULT_NO_SPACE};

typedef struct node NODE;
struct node{
	int data;
	NODE *next;
	NODE *prev;
};

NODE *HEAD;


int maximum_capacity;
int current_capacity;
int page_fault_count;


void remove_tail_node(NODE *HEAD);
void replace_head_node(int new_data);
void swap_head_data(NODE *HEAD, NODE *to_swap);
NODE* create_new_node(int new_data);
void print_working_set();

// int search_list(/**/); search list for


int main(int argc, char *argv[]) {

	return 0;
}

NODE* create_new_node(int new_data){
	NODE *new_node = (NODE*)malloc(sizeof(NODE));
	new_node->data = new_data;
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

void replace_head_node(int new_data){
	NODE *new_node = create_new_node(new_data);

	if(HEAD == NULL){
		HEAD = new_node;
		return;
	}

	HEAD->prev = new_node;
	new_node->next = HEAD;
	HEAD = new_node;

}

void remove_tail_node(NODE *HEAD){

	while(HEAD != NULL){
		HEAD = HEAD->next;
	}
	
	if(HEAD->next == NULL){
		HEAD = NULL;
	}else{
		HEAD->prev->next = NULL;
	}

}

void swap_head_data(NODE *HEAD, NODE *to_swap){
	int temp_data = HEAD->data;
	HEAD->data = to_swap->data;
	to_swap->data = temp_data;
}

void print_working_set(){

}
