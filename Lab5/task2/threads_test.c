/**
* Darius Jones
* Lab 5 Task 2
* 2/23/2018
**/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

typedef enum {
	PRIORITY_HIGH = 99,
	PRIORITY_MEDIUM = 50,
	PRIORITY_LOW = 1
} PRIORITY;

void *runner(void *thread_parameter);

int main(int argc, char const *argv[])
{

	struct sched_param schedparam;
	// SECTION 1: set up RR attr
	pthread_attr_t attr_rr;
	pthread_attr_init(&attr_rr);
	schedparam.sched_priority = PRIORITY_HIGH;
	pthread_attr_setscope(&attr_rr, PTHREAD_SCOPE_PROCESS);
	pthread_attr_setinheritsched(&attr_rr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr_rr, SCHED_RR);
	pthread_attr_setschedparam(&attr_rr, &schedparam);
	// SECTION 2: set up FIFO attr
	pthread_attr_t attr_fifo;
	pthread_attr_init(&attr_fifo);
	schedparam.sched_priority = PRIORITY_MEDIUM;
	pthread_attr_setscope(&attr_fifo, PTHREAD_SCOPE_PROCESS);
	pthread_attr_setinheritsched(&attr_fifo, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr_fifo, SCHED_FIFO);
	pthread_attr_setschedparam(&attr_fifo, &schedparam);
	// SECTION 3: set up OTHER/DEFUALT
	pthread_attr_t attr_oth;
	pthread_attr_init(&attr_oth);
	schedparam.sched_priority = PRIORITY_LOW;
	pthread_attr_setscope(&attr_oth, PTHREAD_SCOPE_PROCESS);
	pthread_attr_setinheritsched(&attr_oth, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr_oth, SCHED_OTHER);
	pthread_attr_setschedparam(&attr_oth, &schedparam);
	// SECTION 4: create array of tids for each type
	pthread_t rr_tid[10];
	pthread_t fifo_tid[10];
	pthread_t oth_tid[10];
	// SECTION 5: create the threads
	char *rr = "PRIORITY_HIGH\0";
	char *fifo = "PRIORITY_MEDIUM\0";
	char *oth = "PRIORITY_LOW\0";
	int count;
	for (count = 0; count < 10; count++) {
		pthread_create(&rr_tid[count], &attr_rr, &runner, rr);
		pthread_create(&fifo_tid[count], &attr_fifo, &runner, fifo);
		pthread_create(&oth_tid[count], &attr_oth, &runner, oth);
	}

	for (count = 0; count < 10; count++) {
		pthread_join(rr_tid[count], NULL);
		pthread_join(fifo_tid[count], NULL);
		pthread_join(oth_tid[count], NULL);
	}

	// SECTION 6:
	while (getchar() != 'q') {
		sleep(1);
	}
	pthread_attr_destroy(&attr_rr);
	pthread_attr_destroy(&attr_fifo);
	pthread_attr_destroy(&attr_oth);
	exit(0);
}

void *runner(void *thread_parameter) {

	int large_number = 100;
	while (large_number != 0) {
		printf("nothing here, just busy work for the thread to do\n");
		large_number--;
		if (large_number == 0) {
			//int pid = getpid();
			printf("tid: %lu %s\n", pthread_self() , thread_parameter);
		}
	}
	pthread_exit(0);
}