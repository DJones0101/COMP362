/**
* Darius Jones
* Lab 3 Task 3
* 2/8/2018
**/

#include "npipe.h"

#define SENDER 1
#define RECEIVER 2
#define QUIT 0


int sender(int named_pipe);
int receiver(int named_pipe);

int mode;
int named_pipe;
char line_1[MAX_LINE];

int main(int argc, char *argv[]) {


	int status = mkfifo("FIFO", 0600);


	if (status < 0) {
		printf("FIFO exist\n");
		printf("set to receiver mode\n");
		mode = RECEIVER;

	} else if (status == 0) {
		printf("creating FIFO\n");
		printf("set to sender mode\n");
		mode = SENDER;

	}


	int quit_program = -1;

	while (true) {

		if (mode == SENDER) {

			quit_program = sender(named_pipe);


			if (quit_program == QUIT) {
				printf("quiting program\n");
				break;
			}

		} else if (mode == RECEIVER) {

			quit_program = receiver(named_pipe);

			if (quit_program == QUIT) {
				printf("quiting program\n");
				break;
			}

		}
	}


	return 0;

}


int sender(int named_pipe) {

	// open a named pipe
	named_pipe = open("FIFO", O_WRONLY);

	// get a line to send
	printf("<send>: ");
	fgets(line_1, MAX_LINE, stdin);
	line_1[strcspn(line_1, "\n")] = '\0';

	//write out the data
	write(named_pipe, line_1, strlen(line_1));
	close(named_pipe);

	if (strcmp(line_1, "quit") == 0) {
		return QUIT;
	}else if(strcmp(line_1, "switch") == 0){

		printf("switching to receiver mode\n");
		mode = RECEIVER;

	}
}


int receiver(int named_pipe) {

	// clearing the array
	memset(line_1, 0, MAX_LINE);

	// open a named pipe
	named_pipe = open("FIFO", O_RDONLY);

	// set the mode to blocking (note '~')
	int flags;
	flags &= ~O_NONBLOCK;
	//flags |= O_NONBLOCK;

	fcntl(named_pipe, F_SETFL, flags);

	// read the data from the pipe
	read(named_pipe, line_1, MAX_LINE);

	close(named_pipe);

	printf("<received>: %s\n", line_1);

	if (strcmp(line_1, "quit") == 0) {
		return QUIT;
	}else if(strcmp(line_1, "switch") == 0){

		printf("switching to sender mode\n");
		mode = SENDER;

	}

	
}