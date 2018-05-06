/*
* Darius Jones
* Project 2 task 4
* 5/5/2018
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/errno.h>
#include <signal.h>
#include <time.h>
#include "sim_dev.h"

#define COUNTDOWN_VALUE 10
timer_t gTimerid;
int count = COUNTDOWN_VALUE;

#define oops(msg, errnum) { perror(msg); exit(errnum); }

#define BUFSIZE 4096

int logaddr, sector_count = 1;
int fd;
int ioctl_control_data = 0XABCDEFEF;
int ioctl_status_data;
REGISTER *disk_status = (REGISTER *) &ioctl_status_data;
REGISTER *disk_control = (REGISTER *) &ioctl_control_data;
extern timer_t gTimerid;
void error_code(int ret_val);

void test() {


	ioctl(fd, IOCTL_SIM_DEV_READ, &ioctl_status_data);

	if (disk_status->ready) {

		time_t rawtime;
		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		printf ( "%s\n", asctime (timeinfo) );
		logaddr = (rand() % 5);

	
		char buffer[128];


		physaddr_t phys;
		log_to_phys(logaddr, &phys);


		disk_control->cyl = phys.cyl;
		disk_control->head = phys.head;
		disk_control->sect = phys.sect;


		disk_control->sector_count = sector_count;
		ioctl(fd, IOCTL_SIM_DEV_WRITE, &ioctl_control_data);
		int retval = read(fd, buffer, 16);

		if (retval == 0) {
			printf("Reading \"%s\" from address %d:\n",  buffer,logaddr);
		}
		else {

			ioctl(fd, IOCTL_SIM_DEV_READ, &ioctl_status_data);
			error_code(disk_status->error_code);
		}

		
	}
	else {

		printf("Waiting for signal\n");
	}



}


void error_code(int ret_val) {
	switch (ret_val) {
	case E_CYL: printf("Error: cyl\n");
	case E_HEAD: printf("Error: head\n");
	case E_SECT: printf("Error:sect\n");
	case E_SECTCOUNT: fprintf(stderr, "bad number of sectors\n");
	case E_RDY: printf("disk not ready\n");
	}
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

int log_to_phys(int logaddr, physaddr_t *phaddr) {
	phaddr->cyl = logaddr / (NUM_OF_HEADS * NUM_OF_SECTS);
	phaddr->head = (logaddr / NUM_OF_SECTS) % NUM_OF_HEADS;
	phaddr->sect = (logaddr % NUM_OF_SECTS) + 1;
	return 0;
}


int main(int ac, char **av) {
	printf("Read started\n");

	fd = open("/dev/sim_dev", O_RDONLY | O_SYNC);
	if ( fd == -1){
		oops("Unable to open device...", 1);
	}

	srand( (unsigned) time(NULL) );
	(void) signal(SIGALRM, timer_callback);
	start_timer();
	while (count >= 0);
}