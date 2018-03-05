/**
* Darius Jones
* Lab 4 Task 1
* 2/15/2018
**/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>


#define NTHREADS 10
#define NFORKS 10
void thread_test();
void fork_test();
double total_fork;
double total_thread;
double times_faster;



void *do_nothing_thread(void *null) {
	int i;
	i = 0;
	pthread_exit(NULL);
}

void do_nothing_fork() {
	int i;
	i = 0;
}

int main(int argc, char *argv[]) {

	fork_test();
	thread_test();

	return 0;

}

void fork_test() {

	struct timeval start;
	struct timeval end;

	int pid, j, status;


	gettimeofday(&start, NULL);

	for (j = 0; j < NFORKS; j++) {


		/*** error handling ***/
		if ((pid = fork()) < 0 ) {
			printf ("fork failed with error code= %d\n", pid);
			exit(0);
		}

		/*** this is the child of the fork ***/
		else if (pid == 0) {
			do_nothing_fork();
			exit(0);
		}

		/*** this is the parent of the fork ***/
		else {

			waitpid(pid, &status, 0);

		}
	}
	gettimeofday(&end, NULL);

	total_fork = (double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec);

	printf ("Fork Total time = %f seconds\n", (total_fork));
}


void thread_test() {

	struct timeval start;
	struct timeval end;


	int rc, j;
	pthread_t tid;
	pthread_attr_t attr;



	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


	gettimeofday(&start, NULL);
	for (j = 0; j < NTHREADS; j++) {


		rc = pthread_create(&tid, &attr, do_nothing_thread, NULL);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}

		/* Wait for the thread */
		rc = pthread_join(tid, NULL);
		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}


	}
	gettimeofday(&end, NULL);


	total_thread = (double) (end.tv_usec - start.tv_usec) / 1000000 + (double) (end.tv_sec - start.tv_sec);

	printf ("Thread Total time = %f seconds\n", (total_thread ));

	double times_faster = total_fork  / total_thread;

	printf("Threads ran about %.1f times faster than forking.\n", times_faster);

	printf("Threads are about 4 times faster than forking.\n");
	printf("Forking creates it's own independent copy of the parent process.\n");
	printf("Copying is the primary reason why forking is slower Threads on the other hand share memory space.\n");


	pthread_attr_destroy(&attr);
	pthread_exit(NULL);




}