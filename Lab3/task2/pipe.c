
/**
* Darius Jones
* Lab 3 Task 2
* 2/8/2018
**/

#include	<sys/types.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include 	<errno.h>
#include 	<sys/wait.h>
#include 	<stdbool.h>

#define MAXLINE 1024
#define READ 0
#define WRITE 1
#define	oops(message)	{ perror(message); exit(EXIT_FAILURE); }


int main(void)
{
	int read_result;
	int fd[2];
	char line_1[MAXLINE];
	char line_2[MAXLINE];
	pid_t fork_result;


	if (pipe(fd) < 0) {oops("Pipe not created");}

	fork_result = fork();

	if (fork_result < 0 ) {
		oops("Fork not created");
	} else if (fork_result == 0) { /*child process*/

		while (true) {

			printf("(child pid: %d) Enter text or \"stop\": ", getpid());

			fgets(line_2, MAXLINE, stdin); // reading from stdin into line_2
			line_2[strcspn(line_2, "\n")] = '\0'; // replaceing \n with \0 for strcmp

			close(fd[READ]);  // closing fd[READ] in order to write
			write(fd[WRITE], line_2, sizeof(line_2));

			if (strcmp(line_2, "stop") == 0) {
				printf("(child pid: %d): stopping\n", getpid());
				exit(EXIT_SUCCESS);
			}
		}



	} else { /*parent process*/

		while (true) {

			close(fd[WRITE]); // closing fd[WRITE] in order to read
			read_result = read(fd[READ], line_1, MAXLINE);

			if (strcmp(line_1, "stop") == 0) {

				if (wait(NULL) < 0) { // parent waiting for child to stop.
					printf("wait(NULL) with errno = %d\n", errno);
				}

				printf("(parent pid: %d): stopping\n", getpid());
				exit(EXIT_SUCCESS);
			}

			printf("\n(parent pid: %d) received: %s\n", getpid(), line_1);

		}

	}

}
