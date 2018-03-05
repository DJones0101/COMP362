/**
* Darius Jones
* Lab 3 Task 1
* 2/8/2018
**/


#include	<errno.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>

#define oops(m) ({fprintf(stderr, "ERROR: %s\n", m); exit(-1);})

int main()
{

	pid_t fork_result_1 = fork();


	if (fork_result_1 < 0) {

		oops("Fork 1 failed");

	} else if (fork_result_1 == 0) { // child 1.1

		pid_t fork_result_1_1 = fork();

		if (fork_result_1_1 < 0) {

			oops("Fork 1.1 failed");

		} else if (fork_result_1_1 == 0) { // child 1.1.1

			printf("1.1.1 PID: %d\n", getpid());

		} else { // parent 1.1
			/*parent will wait for the child to complete */
			printf("1.1 PID: %d\n", getpid());
			if (wait(NULL) < 0) {
				printf("-1 from wait(NULL) with errno = %d\n", errno);
			}

			pid_t fork_result_1_1_2 = fork();

			if (fork_result_1_1_2 < 0) {

				oops("Fork 1.1.2 failed");

			} else if (fork_result_1_1_2 == 0) { // child 1.1.2

				printf("1.1.2 PID: %d\n", getpid());

			} else { // parent 1.1

				if (wait(NULL) < 0) {
					printf("-1 from wait(NULL) with errno = %d\n", errno);
				}
				exit(0);

			}

		}


	} else { // parent 1

		/*parent will wait for the child to complete */
		printf("1 PID: %d\n", getpid());
		if (wait(NULL) < 0) {
			printf("-1 from wait(NULL) with errno = %d\n", errno);
		}


		pid_t fork_result_1_2 = fork();

		if (fork_result_1_2 < 0) {

			oops("Fork 1.2 failed");

		} else if (fork_result_1_2 == 0) { // child 1.2

			pid_t fork_result_1_2_1 = fork();

			if (fork_result_1_2_1 < 0) {

				oops("Fork 1.2.1 failed");

			} else if (fork_result_1_2_1 == 0) { // child 1.2.1

				printf("1.2.1 PID: %d\n", getpid());

			} else {

				printf("1.2 PID: %d\n", getpid());
				if (wait(NULL) < 0) {
					printf("-1 from wait(NULL) with errno = %d\n", errno);
				}


				pid_t fork_result_1_2_2 = fork();

				if (fork_result_1_2_2 < 0) {

				} else if (fork_result_1_2_2 == 0) { // child 1.2.2

					printf("1.2.2 PID: %d\n", getpid());

				} else { // parent 1.2
					if (wait(NULL) < 0) {
						printf("-1 from wait(NULL) with errno = %d\n", errno);
					}
					exit(0);

				}
			}

		} else { // parent 1

			if (wait(NULL) < 0) {
				printf("-1 from wait(NULL) with errno = %d\n", errno);
			}
			exit(0);

		}

	}




}







