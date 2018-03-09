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

enum {ADD_VERTEX = 0, ADD, ADD_EDGE, REMOVE_EDGE, DISPLAY, CHECK, HELP, QUIT, INPUT_ERROR} commands;
char *vertex_names[MAX_NUMBER_OF_VERTICES];
bool adjacency_matrix[MAX_NUMBER_OF_VERTICES][MAX_NUMBER_OF_VERTICES];
int number_of_vertices = 0;
char commands_in[STRING_MAX_SIZE];
char command1[STRING_MAX_SIZE], command2[STRING_MAX_SIZE], command3[STRING_MAX_SIZE];


int get_index_of_vertex(char *vertex_name);
void add_vertex(char *vertex_name);
void add_edge(char *from_vertex_name, char *to_vertex_name);
void remove_edge(char *from_vertex_name, char *to_vertex_name);
int get_command_indexes(char *commands);
void display_adjacency_matrix();
bool check_for_cycle();
void display_help();
void free_names();


int main(int argc, char *argv[]) {
	int count;
	for (count = 0; count < STRING_MAX_SIZE; count++) {vertex_names[count] = malloc(sizeof(char) * STRING_MAX_SIZE);}
	int index;

	while (true) {

		printf("Enter a command: ");
		fscanf(stdin, "%s", commands_in);

		switch (get_command_indexes(commands_in)) {

		case ADD:

			fscanf(stdin, "%s", command1);
			index = get_command_indexes(command1);

			if ( index == ADD_VERTEX) { // add vertex Aaa
				//memset(&command2[0], 0, sizeof(command2));
				fscanf(stdin, "%s", command2);
				add_vertex(command2);


			} else if (index == ADD_EDGE) { // add edge Aaa Bbbb

				fscanf(stdin, "%s %s", command2, command3);
				add_edge(command2, command3);
			} else if (index == INPUT_ERROR) {
				printf("Invalid Command\n"); break;
			}

			break;
		case REMOVE_EDGE: break; //fscanf(stdin,"%s %s")  get the next 2 strings call remove_edge() break;
		case DISPLAY: display_adjacency_matrix(); break;
		case CHECK: break; //if(check_for_cycle() == true){printf(">> DEADLOCKED <<\n")}else{printf(">> NO DEADLOCK <<\n")};
		case HELP: display_help(); break;
		case QUIT: printf("Exiting the program.\n"); exit(EXIT_SUCCESS);
		default: printf("Invalid Command\n"); break;
		}
	}

	return 0;
}

int get_index_of_vertex(char *vertex_name) {

}

void add_vertex(char *vertex_name) {

	if (number_of_vertices == MAX_NUMBER_OF_VERTICES) {
		printf("The maximum limit of vertices (20) has been already reached.\n");
		return;
	} else {

		int count;
		for (count = 0; count < number_of_vertices; count++) {
			if (strcmp(vertex_names[count], vertex_name) == 0) {
				printf("There is already a vertex with the name %s.\n", vertex_name);
				return;
			}

		}
		strcpy(vertex_names[number_of_vertices], vertex_name);
		number_of_vertices++;
	}


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

	if (number_of_vertices == 0) {

		printf("Unable to display adjacency matrix. There are no vertices yet\n");
		return;

	} else {

		int count;
		
		for (count = 0; count < number_of_vertices; count++) {
			printf("\t");
			printf("%-10s", vertex_names[count]);
		}printf("\n");

		int row;
		int col;
		count = 0;
		for (row = 0; row < number_of_vertices; row++) {
			printf("\t");
			printf("%s ",vertex_names[count]);

			for (col = 0; col < number_of_vertices; col++) {

				
				if (adjacency_matrix[row][col] == true) {
					printf("%-10d", 1);
				} else {
					printf("%-10d", 0);
				}

			}
			count++;
			printf("\n");
		}

	}
}

bool check_for_cycle() {

}

int get_command_indexes(char *commands) {

	if (strcmp(commands, "vertex") == 0) {

		return ADD_VERTEX;

	} else if ( strcmp(commands, "edge") == 0) {

		return ADD_EDGE;

	} else if ( strcmp(commands, "remove edge") == 0) {

		return REMOVE_EDGE;

	} else if ( strcmp(commands, "check") == 0) {

		return CHECK;

	} else if ( strcmp(commands, "help") == 0) {

		return HELP;

	} else if (strcmp(commands, "add") == 0) {

		return ADD;
	}
	else if (strcmp(commands, "quit") == 0) {

		return QUIT;
	} else if (strcmp(commands, "display") == 0) {
		return DISPLAY;
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