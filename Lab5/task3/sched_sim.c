/**
* Darius Jones
* Lab 5 Task 3
* 2/25/2018
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define NUM_OF_PROCESSES 3
#define MAX_SIZE 5
#define DONE -1

bool SRTF = false;
bool quantum_reset = false;
double waiting_processes[NUM_OF_PROCESSES];
char algorithm[MAX_SIZE];
int process_q[NUM_OF_PROCESSES];
int (*shceduler)(int);
int rr(int current_process_index);
int srtf(int current_process_index);
int fcfs(int current_process_index);
int sjf(int current_process_index);
void set_scheduling_algorithm();
void simulation();
bool remaining_work_check();
void display_CPU(int current_time, int current_process_index);
void count_waiting_processes(int current_process_index);
bool check_for_event(int current_time, int next_incoming_process_time);
int work_remains(int current_process_index);
int average_waiting_time();
int full_quantum, remaining_quantum;
int current_process_index = 0;
int next_incoming_process_time;
int next_incoming_process;
int current_time = 0;
int scan_index = 0;

int main(int argc, char *argv[]) {
	set_scheduling_algorithm();
	simulation();
}

void simulation() {


	/*Implement your program in such a way that the scheduling
	algorithm just selects which process should be worked on, while
	the main actually decremements the work needed to be done. */

	fscanf(stdin, "%d %d", &next_incoming_process_time, &process_q[current_process_index]);

	while (1) {

		if (check_for_event(current_time, next_incoming_process_time) == true) {

			display_CPU(current_time, current_process_index);
			if (fscanf(stdin, "%d %d", &next_incoming_process_time, &next_incoming_process) != EOF) {
				scan_index++;
				process_q[scan_index] = next_incoming_process;
			}
		}

		if (current_process_index == DONE) {
			double sum = waiting_processes[0] + waiting_processes[1] + waiting_processes[2];
			double average = sum / NUM_OF_PROCESSES;
			printf("AVERAGE WAITING TIME: %.2lf\n", average);
			break;
		}
		current_process_index = shceduler(current_process_index);
		count_waiting_processes(current_process_index);
		//printf("current_process_index %d value %d\n", current_process_index, process_q[current_process_index] );
		process_q[current_process_index]--;
		current_time++;

	}



}
void set_scheduling_algorithm() {

	// read in the first string and set the algorithm

	fscanf(stdin, "%s", &algorithm);

	if (strcmp(algorithm, "RR") == 0) {
		fscanf(stdin, "%d", &full_quantum);
		remaining_quantum = full_quantum;
		shceduler = &rr;
	} else if (strcmp(algorithm, "FCFS") == 0) {
		shceduler = &fcfs;
	} else if (strcmp(algorithm, "SRTF") == 0) {
		shceduler =  &srtf;
	} else {
		shceduler = &sjf;
	}
}


int rr(int current_process_index) {
	// check the quantum and check for dead processes
	if (remaining_quantum == 0 || process_q[current_process_index] == 0) {

		if (current_process_index == NUM_OF_PROCESSES - 1) {
			current_process_index = 0;
		} else {
			current_process_index++;
		}

		remaining_quantum = full_quantum;
		display_CPU(current_time, current_process_index);
	}

	if (remaining_work_check() == false) {

		return DONE;
	}
	remaining_quantum--;
	return current_process_index;
}

int srtf(int current_process_index) {
// constanly check for the smallest value;
	SRTF = true;
	return sjf(current_process_index);
}

int fcfs(int current_process_index) {
// linear search, find first job that needs work done.
	if (remaining_work_check() == true) {

		if (process_q[current_process_index] != 0) {
			return current_process_index;
		} else {

			current_process_index++;
			display_CPU(current_time, current_process_index);
		}

	} else {
		return DONE;
	}

	return current_process_index;
}

int sjf(int current_process_index) {
// search for smallest job, if processes to work on.
	int min = INT_MAX;
	int original = current_process_index;
	bool change_flag = false;
	int current_p = process_q[current_process_index];
	if (SRTF == true) {
		current_p = 0;
	}
	if (remaining_work_check() == true) {

		if (current_p == 0) {
			int count;
			for (count = 0; count < NUM_OF_PROCESSES; count++) {
				if (process_q[count] != 0 && process_q[count] < min) {
					min = process_q[count];
					current_process_index = count;
					change_flag = true;

				}
			}
			if (change_flag == true) {
				if (SRTF == false ) {
					display_CPU(current_time, current_process_index);
				} else if (SRTF == false) {
					if (original != current_process_index) {
						display_CPU(current_time, current_process_index);
					}
				}
				change_flag = false;
			}

		}

	} else {
		return DONE;
	}

	return current_process_index;

}

void display_CPU(int current_time, int current_process_index) {
	// display cpu and queue information.
	printf("T%d:\n", current_time);
	int CPU = process_q[current_process_index];
	if (CPU == 0) {
		printf("CPU: <IDLE>\n");
		printf("QUEUE: \n");
	} else if (CPU != 0) {
		printf("CPU: P%d[%d]\n", current_process_index + 1, CPU);
		printf("QUEUE: ");
		int count;
		for (count = 0; count < NUM_OF_PROCESSES; count++) {
			if (process_q[count] != 0 && current_process_index != count) {
				printf("P%d[%d] ", count + 1, process_q[count] );
			}
		}
		printf("\n");
	}

	printf("\n");
}

bool remaining_work_check() {
	// checks if there's remaining work
	int count;
	int tracker = 0;
	for (count = 0; count < NUM_OF_PROCESSES; count++) {
		if (process_q[count] == 0) {
			tracker++;
		}
	}
	if (tracker == 3) { return false;}

	return true;
}
bool check_for_event(int current_time, int next_incoming_process_time) {

	if (current_time ==  next_incoming_process_time) {
		return true;
	}
	return false;

}

void count_waiting_processes(int current_process_index) {
	int count;
	for (count = 0; count < NUM_OF_PROCESSES; count++) {
		if (process_q[current_process_index] != process_q[count] && process_q[count] != 0) {
			waiting_processes[count]++;
		}
	}
}


