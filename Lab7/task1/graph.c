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
	int row, col;
	for (row = 0; row < MAX_NUMBER_OF_VERTICES; row++) {
		for (col = 0; col < MAX_NUMBER_OF_VERTICES; col++) {
			adjacency_matrix[row][col] = false;
		}
	}
	int index;

	while (true) {

		printf("Enter a command: ");
		fscanf(stdin, "%s", commands_in);

		switch (get_command_indexes(commands_in)) {

		case ADD_VERTEX: fscanf(stdin, "%s", command1); add_vertex(command1); break;
		case ADD_EDGE: fscanf(stdin, "%s %s", command1, command2); add_edge(command1, command2); break;
		case REMOVE_EDGE: fscanf(stdin, "%s %s", command1, command2); remove_edge(command1, command2); break;
		case DISPLAY: display_adjacency_matrix(); break;
		case CHECK: break; //if(check_for_cycle() == true){printf(">> DEADLOCKED <<\n")}else{printf(">> NO DEADLOCK <<\n")};
		case HELP: display_help(); break;
		case QUIT: printf("Exiting the program.\n"); exit(EXIT_SUCCESS);
		default: printf("Invalid Command\n"); break;

		}
	}

	free_names(vertex_names);

	return 0;
}

int get_index_of_vertex(char *vertex_name) {

	int count;
	int return_val = -1;
	for (count = 0; count < MAX_NUMBER_OF_VERTICES; count++) {
		if (strcmp(vertex_name, vertex_names[count]) == 0) {
			return_val = count;
			break;
		}
	}

	return return_val;
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
		printf("Added a new vertex named %s at index %d.\n", vertex_name, number_of_vertices);
		number_of_vertices++;
	}


}

void add_edge(char *from_vertex_name, char *to_vertex_name) {

	int index1 = get_index_of_vertex(from_vertex_name);
	int index2 = get_index_of_vertex(to_vertex_name);

	if (index1 == index2) {
		printf("A vertex cannot be connected to itself.\n");
		return;
	}

	if (index2 != -1 || index1 !=  -1) {

		bool result = adjacency_matrix[index1][index2];
		if (result == false) {
			adjacency_matrix[index1][index2] = true;
			printf("Added edge from vertex %s to vertex %s.\n", from_vertex_name, to_vertex_name);
		} else {
			printf("That edge already exists.\n");
		}

	} else {
		printf("One or more of those vertices do not exist.\n");
	}


}

void remove_edge(char *from_vertex_name, char *to_vertex_name) {


	int index1 = get_index_of_vertex(from_vertex_name);
	int index2 = get_index_of_vertex(to_vertex_name);

	if (index2 != -1 || index1 !=  -1) {

		bool result = adjacency_matrix[index1][index2];
		if (result == true) {
			adjacency_matrix[index1][index2] = false;
			printf("Removed the edge from vertex %s to vertex %s.\n", from_vertex_name, to_vertex_name);
		} else {
			printf("No edge exists between those two vertices.\n");
		}

	} else {
		printf("One or more of those vertices do not exist.\n");
	}
}


void display_adjacency_matrix() {

	// needs work

	if (number_of_vertices == 0) {

		printf("Unable to display adjacency matrix. There are no vertices yet\n");
		return;

	} else {

		int count;
		printf("\t\t");

		for (count = 0; count < number_of_vertices; count++) {

			printf("  %10s", vertex_names[count]);
		} printf("\n");

		int row;
		int col;
		count = 0;
		for (row = 0; row < number_of_vertices; row++) {

			printf("\t%10s", vertex_names[count]);

			for (col = 0; col < number_of_vertices; col++) {


				if (adjacency_matrix[row][col] == true) {
					printf("%10d", 1);
				} else {
					printf("%10d", 0);
				}

			}
			count++;
			printf("\n");
		}

	}
}

bool check_for_cycle() {
	int row, col;
	bool previous;

	for(row = 1; row < number_of_vertices; row++){
		adjacency_matrix[row][col];
		for(col = 0; col < number_of_vertices; col++){
			if(){

			}
		}
	}
}

int get_command_indexes(char *commands) {

	if (strcmp(commands, "add") == 0) {

		fscanf(stdin, "%s", commands);
		if (strcmp(commands, "vertex") == 0) {
			return ADD_VERTEX;
		} else if (strcmp(commands, "edge") == 0) {
			return ADD_EDGE;
		}

	} else if ( strcmp(commands, "remove") == 0) {

		fscanf(stdin, "%s", commands);
		if (strcmp(commands, "edge") == 0) {
			return REMOVE_EDGE;
		}

	} else if ( strcmp(commands, "check") == 0) {

		return CHECK;

	} else if ( strcmp(commands, "help") == 0) {

		return HELP;

	} else if (strcmp(commands, "quit") == 0) {

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

	int count;
	for (count = 0; count < MAX_NUMBER_OF_VERTICES; count++) {
		free(vertex_names[count]);
	}

}
