/*
* Darius Jones
* Lab7 Task 1
* 3/8/2018
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STRING_MAX_SIZE 50
#define MAX_NUMBER_OF_VERTICES 20

enum {ADD_VERTEX = 0, ADD_EDGE, REMOVE_EDGE, DISPLAY, CHECK, HELP, QUIT, INPUT_ERROR} commands;
char *vertex_names[MAX_NUMBER_OF_VERTICES];
bool adjacency_matrix[MAX_NUMBER_OF_VERTICES][MAX_NUMBER_OF_VERTICES];
int number_of_vertices = 0;
char commands_in[STRING_MAX_SIZE];

int get_index_of_vertex(char *vertex_name);
void add_vertex(char *vertex_name);
void add_edge(char *from_vertex_name, char *to_vertex_name);
void remove_edge(char *from_vertex_name, char *to_vertex_name);
int get_command_indexes(char commands[]);
void display_adjacency_matrix();
bool check_for_cycle();
void display_help();
void free_names();


int main(int argc, char *argv[]) {

	while (true) {
		printf("Enter a command: ");
		fscanf(stdin, "%s", commands_in);
		commands_in[strcspn(commands_in, "\n")] = '\0'; // removes \n

		switch (get_command_indexes(commands_in)) {
		case ADD_VERTEX: break;// fscanf(stdin,"%s") get the next string call add_vertex() break;
		case ADD_EDGE: break; // fscanf(stdin,"%s %s") get the  next 2 strings call add edge
		case REMOVE_EDGE: break; //fscanf(stdin,"%s %s")  get the next 2 strings call remove_edge() break;
		case DISPLAY: break; // call display_adjacency_matrix() break;
		case CHECK: break; //if(check_for_cycle() == true){printf(">> DEADLOCKED <<\n")}else{printf(">> NO DEADLOCK <<\n")};
		case HELP: display_help(); break;
		case QUIT: printf("Exiting the program.\n"); exit(EXIT_SUCCESS);
		case INPUT_ERROR: printf("Invalid command\n"); break;
		default: printf(" Invalid command\n");

		}
	}

	return 0;
}

int get_index_of_vertex(char *vertex_name) {

}

void add_vertex(char *vertex_name) {

	// "maybe"
	// add the vertex name to the char *vertex_names[]


}

void add_edge(char *from_vertex_name, char *to_vertex_name) {

	// get the index of from_vertex and to_vertex and find it's place
	// int the adjacency_matrix

}

void remove_edge(char *from_vertex_name, char *to_vertex_name) {

	// "maybe"
	// get the from_vertex and the to_vertex
	// then remove it from adjacency_matrix maybe replace 1 with 0
	// remove it from the vertex_names array
}

void display_adjacency_matrix() {
	int row;
	int col;
	// if graph is empty 
	// printf("Unable to display adjacency matrix. There are no vertices yet.")

	/*
	for(row = 0; row < MAX_NUMBER_OF_VERTICES; row++){

		printf("%s ", vertex_names[row]);

		for(col = 0; col < MAX_NUMBER_OF_VERTICES; col++){

			printf("%s ",vertex_names[col]);
			printf("%d ", adjacency_matrix[row][col]);
			first row and first col is the names	

		}
		printf("\n");
	}*/
}

bool check_for_cycle() {

}

int get_command_indexes(char commands[]) {

	if (strcmp(commands, "add vertex") == 0) {
		return ADD_VERTEX;
	} else if ( strcmp(commands, "add edge") == 0) {
		return ADD_EDGE;
	} else if ( strcmp(commands, "remove edge") == 0) {
		return REMOVE_EDGE;
	} else if ( strcmp(commands, "check") == 0) {
		return CHECK;
	} else if ( strcmp(commands, "help") == 0) {
		return HELP;
	} else if (strcmp(commands, "quit") == 0) {
		return QUIT;
	}

	return INPUT_ERROR;
}

void display_help() {
	printf("The following commands are available for use:\n");
	printf("	add vertex <vertex_name>\n");
	printf("	add edge <from_vertex_name> <to_vertex_name>\n");
	printf("	remove edge <from_vertex_name> <to_vertex_name>\n");
	printf("	display \n");
	printf("	check\n");
	printf("	help\n");
	printf("	quit\n");
	printf("Angled brackets such as: <info> represent user defined information.\n");
}

void free_names() {

	/*int count;
	for (count = 0; count < MAX_NUMBER_OF_VERTICES; count++) {
		free(vertex_name[count]);
	}*/

}