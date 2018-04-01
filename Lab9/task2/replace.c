/*
* Darius Jones
* Lab 9 Task 2
* 3/29/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {FAULT_SPACE = 0, FAULT_NO_SPACE};

typedef struct node NODE;
struct node {
	int data;
	NODE *next;
	NODE *prev;
};

NODE *HEAD;


int maximum_capacity;
int current_capacity;
int fault_count;
int found_at;

void remove_tail_node();
void append_to_head(int new_data);
void swap_data(int data1, int data2);
void swap_it_up( int found_at);
NODE* create_new_node(int new_data);
void print();
void free_nodes();
void insert_last(int new_data);
void simulation();
NODE *search_list(int data);


int main(int argc, char *argv[]) {
	simulation();
	return 0;
}

void simulation() {

	fscanf(stdin, "%d", &maximum_capacity);

	int current_input;
	NODE *search_result;
	

	while (true) {

		if (fscanf(stdin, "%d", &current_input) == EOF) {break;}
		
		search_result = search_list(current_input);

		if (search_result != NULL && found_at != -1) { 

			
			printf(">");
			swap_it_up(found_at);

		} else { 

			fault_count++;
			printf("*");

			if( current_capacity < maximum_capacity){

				append_to_head(current_input);

			}else{

				append_to_head(current_input);
				remove_tail_node();
			}

			current_capacity++;
			

		}
		print();

	}

	printf("Page faut count: %d\n",fault_count);


}



NODE *search_list(int data) {
	NODE *current = HEAD;
	found_at = -1;

	while (current != NULL) {

		found_at++;

		if (current->data == data) {
			
			return current;
		}

		current = current->next;
	}

	
	return NULL;
}


NODE* create_new_node(int new_data) {
	NODE *new_node = (NODE*)malloc(sizeof(NODE));
	new_node->data = new_data;
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

void insert_last(int new_data) {

	NODE *to_insert = create_new_node(new_data);
	NODE *current = HEAD;

	while (current != NULL) {
		current = current->next;
	}

	current->next = to_insert;
	to_insert->prev = current;
	to_insert->next = NULL;

}


void append_to_head(int new_data) {
	NODE *new_node = create_new_node(new_data);

	if (HEAD == NULL) {
		HEAD = new_node;
		return;
	}

	HEAD->prev = new_node;
	new_node->next = HEAD;
	HEAD = new_node;

}

void remove_tail_node() {

	NODE *current = HEAD;

	while (current->next != NULL) {
		current = current->next;
	}

	current->prev->next =NULL;
	free(current);

}

void swap_it_up(int found_at){

	int index = 0;

	NODE *current = HEAD;
	while(current != NULL && index != found_at){
		current = current->next;
		index++;
	}

	while( current->prev != NULL && index != 0){
		
		swap_data(current->data, current->prev->data);
		current = current->prev;

	}

}

void swap_data(int data1, int data2) {
	int temp_data = data1;
	data1 = data2;
	data2 = temp_data;
}

void print() {
	NODE *current = HEAD;

	while(current != NULL){
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

void free_nodes() {

	NODE *current = HEAD;

	while (current != NULL) {
		NODE *next_node = current->next;
		free(current);
		current = next_node;
	}
}
