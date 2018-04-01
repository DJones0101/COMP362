/*
* Darius Jones
* Lab 9 Task 2
* 3/29/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define YES 0
#define NO 1



typedef struct node NODE;
struct node {
	int data;
	NODE *next;
	NODE *prev;
};

NODE *HEAD;


int maximum_capacity;
int current_capacity;
int fault_count = 0;

void remove_tail_node();
void append_to_head(int new_data);
void swap_data(int& data1, int& data2);
void swap_it_up( int current_input);
NODE* create_new_node(int new_data);
void print(int fault_stat);
void free_nodes();
void insert_last(int new_data);
void simulation();
bool search_list(int data);
void fault_space(int current_input);
void fault_no_space(int current_input);
void hit(int current_input);
void print_test();


int main(int argc, char *argv[]) {
	simulation();
	return 0;
}

void simulation() {

	fscanf(stdin, "%d", &maximum_capacity);

	int current_input;
	bool search_result = false;


	while (fscanf(stdin, "%d", &current_input) != EOF) {

		search_result = search_list(current_input);

		if (search_result == false && current_capacity < maximum_capacity) {

			fault_space(current_input);

		} else if (search_result == false && current_capacity == maximum_capacity ) {

			fault_no_space(current_input);

		} else if (search_result == true) {
			hit(current_input);
		}

	}

	printf("Page faut count: %d\n", fault_count);


}



bool search_list(int data) {

	NODE *current = HEAD;

	while (current != NULL) {

		if (current->data == data) {

			return true;
		}

		current = current->next;
	}
	return false;
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
	current_capacity++;

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
	current_capacity--;

	while (current->next != NULL) {
		current = current->next;
	}

	current->prev->next = NULL;
	free(current);

}

void swap_it_up(int current_input) {

	NODE *current = HEAD;
	int count = 0;
	while (current != NULL) {

		if (current->data == current_input) {break;}
		count++;
		current = current->next;
	}

	int count_to;
	for(count_to = 0; count_to < count; count_to++){
		printf("SWAPPING %d & %d\n", current->prev->data,current->data);
		swap_data(current->prev->data,current->data);
		print_test();
		current = current->prev;
	}


}

void swap_data(int& data1, int& data2) {
	int temp_data = data1;
	data1 = data2;
	data2 = temp_data;
}

void print(int fault_stat) {
	NODE *current = HEAD;

	if (fault_stat == YES) {
		printf("*");
	} else if (fault_stat == NO) {
		printf(">");
	}

	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

void print_test() {
	NODE *current = HEAD;
	printf("TEST--------------");
	while (current != NULL) {
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

void fault_no_space(int current_input) {
	remove_tail_node();
	append_to_head(current_input);
	fault_count++;
	print(YES);
}

void fault_space(int current_input) {
	append_to_head(current_input);
	fault_count++;
	print(YES);
}

void hit(int current_input){
	swap_it_up(current_input);
	print(NO);

}