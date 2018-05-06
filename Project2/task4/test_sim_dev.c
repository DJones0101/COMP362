/*
* Darius Jones
* Project 2 task 3
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


#include "sim_dev.h"

#define oops(msg, errnum) { perror(msg); exit(errnum); }

#define BUFSIZE 4096



int main(void)
{
	int fd, ret_val, wlen, tmp, tmp2;

	// test message to send to the device
	char msg[128] = "Skeleton Kernel test";
	char receive_buffer[128];

	// variables for holding device control data
	int ioctl_control_data = 0XABCDEFEF;
	int ioctl_status_data = 0x00000000;
	REGISTER *disk_status_reg = (REGISTER *) &ioctl_status_data;
	REGISTER *disk_control = (REGISTER *) &ioctl_control_data;

	// bit fields
	int starting_sector = 2;
	disk_control->ready = 1;
	disk_control->cyl = 2;
	disk_control->head = 2;
	disk_control->sect = starting_sector;
	disk_control->sector_count = 0;

	// open the I/O channel to the device
	fd = open("/dev/sim_dev", O_RDWR | O_SYNC);
	if ( fd == -1) {
		oops("Unable to open device...", 1);
	}
	
	disk_control->sect = disk_control->sect + 2;
	disk_control->sector_count = disk_control->sector_count + 1;
	// set disk control register
	ioctl(fd, IOCTL_SIM_DEV_WRITE, &ioctl_control_data);
	// test device write function
	ret_val = write(fd, msg, 15);
	error_code(ret_val);
	printf("'%s' wrote to /dev/sim_dev\n", msg);
	read(fd, receive_buffer, 15);
	ioctl(fd, IOCTL_SIM_DEV_READ, &ioctl_status_data);
	error_code(disk_status_reg->error_code);
	printf("'%s' read from /dev/sim_dev\n", receive_buffer);
	disk_control->sect = starting_sector;
	disk_control->sector_count = 10;
	ioctl(fd, IOCTL_SIM_DEV_WRITE, &ioctl_control_data);
	read(fd, receive_buffer, 128);
	printf("'%s' read from /dev/sim_dev\n", receive_buffer);

	close(fd);
}

int log_to_phys(int logaddr, physaddr_t *phaddr) {
	phaddr->cyl = logaddr / (NUM_OF_HEADS * NUM_OF_SECTS);
	phaddr->head = (logaddr / NUM_OF_SECTS) % NUM_OF_HEADS;
	phaddr->sect = (logaddr % NUM_OF_SECTS) + 1;
	return 0;
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
