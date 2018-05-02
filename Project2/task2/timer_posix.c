/*
* Darius Jones
* Project 2 task 1
* 4/26/2018
*/

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include "disk.h"

#define COUNTDOWN_VALUE 10
timer_t gTimerid;
int count = COUNTDOWN_VALUE;

void test() {


	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	char *string = malloc(sizeof(char) * SECT_SIZE);
	char *string2 = malloc(sizeof(char) * SECT_SIZE);
	memset(string,'\0', strlen(string));
	memset(string2,'\0', strlen(string2));

	int event = rand() % 2;
	
	//int sects = (strlen(string) / SECT_SIZE) + 1;

	physical_address *phys = malloc(sizeof(physical_address));
	

	//printf("Random string generated \"%s\".\n", string);

	if (event == 1) {
		physical_address *phys = malloc(sizeof(physical_address));
		int address = (rand() % MAX_LOGICAL_SECTOR) + 1;
		log_to_phys(address, phys);
		read(address, 1, (void**)string);
		printf("Reading string \"%s\"\nFrom Physical address: (%d, %d, %d)\nLogical address: %d\n", string, phys->head, phys->cyl, phys->sect, address);
		printf ( "%s\n", asctime (timeinfo) );


	} else if (event == 0) {
		physical_address *phys = malloc(sizeof(physical_address));
		int address = (rand() % MAX_LOGICAL_SECTOR) + 1;
		log_to_phys(address, phys);
		random_string(string2, 15);
		printf("Wrote string \"%s\"\nTo Physical address: (%d, %d, %d)\nLogical address: %d\n", string2, phys->head, phys->cyl, phys->sect, address);
		write(address, 1, string2);
		printf ( "%s\n", asctime (timeinfo) );

	}

	free(string);
	free(string2);
	free(phys);


}

void start_timer(void) {
	struct itimerspec value;
	value.it_value.tv_sec = 1;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = 1;
	value.it_interval.tv_nsec = 0;
	timer_create (CLOCK_REALTIME, NULL, &gTimerid);
	timer_settime (gTimerid, 0, &value, NULL);
}

void stop_timer(void) {
	struct itimerspec value;
	value.it_value.tv_sec = 0;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = 0;
	value.it_interval.tv_nsec = 0;
	timer_settime (gTimerid, 0, &value, NULL);
}

void timer_callback(int sig) {
	//printf("Caught timer signal: %d ... !!\n", sig);
	test();
	count--;
}

int main(int ac, char **av) {
	srand( (unsigned) time(NULL) );
	(void) signal(SIGALRM, timer_callback);
	start_timer();
	while (count >= 0);
}