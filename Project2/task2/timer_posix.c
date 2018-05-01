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
	srand(time(&rawtime));
	timeinfo = localtime ( &rawtime );
	char *string = malloc(sizeof(char) * SECT_SIZE);
	random_string(string, 15);
	int event = rand() % 1;
	int address = rand() % MAX_LOGICAL_SECTOR;
	int sects = (strlen(string) / SECT_SIZE) + 1;

	physical_address phys;
	log_to_phys(address, &phys);

	printf("Random string generated \"%s\".\n", string);
	printf("Logical address: %d\n", address);
	printf("Physical address (%d, %d, %d)\n", phys.head, phys.cyl, phys.sect);
	printf ( "%s\n", asctime (timeinfo) );

	if (event == 1) {

		read(address, sects, (void**)string);
		printf("Read string \"%s\".\n", string);



	} else if (event == 0) {

		printf("Wrote string \"%s\".\n", string);
		write(address, sects, string);

	}

	free(string);
	

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
	(void) signal(SIGALRM, timer_callback);
	start_timer();
	while (count >= 0);
}