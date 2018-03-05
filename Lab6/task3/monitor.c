/*
* Darius Jones
* Lab 6 Task 3
* 3/2/2018
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#define NUM_OF_PHILOSOPHERS 5
#define DEFUALT_NUMBER_OF_TURNS 4
#define DELAY ( (rand() % 5 + 1) * 1000)

enum {THINKING, HUNGRY, EATING};
pthread_cond_t condition[NUM_OF_PHILOSOPHERS];
pthread_mutex_t mutex;
int state[NUM_OF_PHILOSOPHERS];


int get_left(int philosopher);
int get_right(int philosopher);
void try_to_eat(int philosopher);
void try_to_pickup(int philosopher);
bool is_eating(int philosopher);
void putdown_chopsticks(int philosopher);
void *runner(void *philo);

struct param_data
{
	int philo_id;
	int turns;
}param_data;



int main(int argc, char *argv[]) {


	if (argc < 2) {
		printf("Usage: monitor <number of turns>\n");
		return 1;
	}
	int turn_num_in = atoi(argv[1]);
	// create the threads
	srand(time(NULL));
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_t seats[NUM_OF_PHILOSOPHERS];
	struct param_data *data;

	int philosopher;
	for (philosopher = 0; philosopher < NUM_OF_PHILOSOPHERS; philosopher++) {
		data = (struct param_data* )malloc(sizeof(param_data));
		data->philo_id = philosopher;
		data->turns = turn_num_in;
		pthread_create(&seats[philosopher], NULL, runner, data);
	}

	for (philosopher = 0; philosopher < NUM_OF_PHILOSOPHERS; philosopher++) {

		pthread_join(seats[philosopher], NULL);
	}
	printf ("Dinner is no more.\n");

	return 0;
}

int get_left(int philosopher) {
	return (philosopher + 4) % 5;
}

int get_right(int philosopher) {
	return (philosopher + 1) % 5;
}

void try_to_pickup(int philosopher) {


	pthread_mutex_lock(&mutex);// lock

	state[philosopher] = HUNGRY;
	try_to_eat(philosopher);

	if (is_eating(philosopher) == false) {

		pthread_cond_wait(&condition[philosopher], &mutex);//wait

	} 
		
	

	pthread_mutex_unlock(&mutex);// unlock
}

void putdown_chopsticks(int philosopher) {

	pthread_mutex_lock(&mutex);// lock
	state[philosopher] = THINKING;
	printf ("Philsopher %d has returned chopsticks\n", philosopher);
	printf ("Philsopher %d is thinking\n", philosopher);
	int left = get_left(philosopher);
	int right = get_right(philosopher);
	try_to_eat(left);
	try_to_eat(right);
	pthread_mutex_unlock(&mutex);// unlock
}

bool is_eating(int philosopher) {

	if (state[philosopher] == EATING) {
		return true;
	}
	return false;
}

void try_to_eat(int philosopher) {
	int left = get_left(philosopher);
	int right = get_right(philosopher);

	if (state[philosopher] == HUNGRY && (is_eating(left) == false) && (is_eating(right) == false)) {
		state[philosopher] = EATING;
		printf ("Philsopher %d grabbed the chopsticks and is eating\n", philosopher);
		pthread_cond_signal(&condition[philosopher]);// signal
	}
}

void *runner(void *philo_id) {

	struct param_data *data = philo_id;
	int philosopher = data->philo_id;
	int turns = data->turns;
	printf ("Philsopher %d sits at the table.\n", data->philo_id);
	usleep (DELAY);
	int turn_number;
	for (turn_number = 0; turn_number < turns; turn_number++) {
		printf ("Philsopher %d gets hungry for the %d time!\n", philosopher, turn_number + 1);
		try_to_pickup(philosopher);
		putdown_chopsticks(philosopher);
		printf ("Philsopher %d finished turn %d\n", philosopher, turn_number + 1);
	}
	printf (">>>>>> Philsopher %d finished meal. <<<<<<\n", philosopher);
	free(data);
	pthread_exit(EXIT_SUCCESS);
}

