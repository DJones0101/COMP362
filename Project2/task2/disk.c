/*
* Darius Jones
* Project 2 task 1
* 4/26/2018
*/

#include "disk.h"


int log_to_phys(int logical_address, physical_address *phys_address) {


	/*C = LBA ÷ (HPC × SPT)
	  H = (LBA ÷ SPT) mod HPC
	  S = (LBA mod SPT) + 1*/

	phys_address->cyl = logical_address / (NUM_OF_HEADS * NUM_OF_SECTS);
	phys_address->head = (logical_address / NUM_OF_SECTS) % NUM_OF_HEADS ;
	phys_address->sect = (logical_address % NUM_OF_SECTS) + 1;

	if ((phys_address->cyl <= NUM_OF_CYLS) && (phys_address->head <= NUM_OF_HEADS) && (phys_address->sect <= NUM_OF_SECTS)) {
		return VALID;
	}

	return INVALID;

}

int phys_to_log(physical_address *phys_address) {

	/*LBA = (C × HPC + H) × SPT + (S - 1)*/
	return (phys_address->cyl * NUM_OF_HEADS + phys_address->head) *  NUM_OF_SECTS + (phys_address->sect - 1);

}

int read(int logical_block_num, int num_of_blocks, void **buffer) {

	if (is_valid(logical_block_num, num_of_blocks) == true) {
		physical_address phaddr;
		log_to_phys(logical_block_num, &phaddr);
		int count;

		for (count = 0; count < num_of_blocks; count++) {
			strcpy(((char *)buffer), &(disk[count][phaddr.cyl][phaddr.head][phaddr.sect]));
		}
		return 0;


	}

	return -1;
}

int write(int logical_block_num, int num_of_sectors, void *buffer) {

	if (is_valid(logical_block_num, num_of_sectors) == true) {

		physical_address phaddr;

		log_to_phys(logical_block_num, &phaddr);
		char *value = malloc(sizeof((char*)buffer));
		strcpy(value, buffer);
		int count;
		for (count = 0; count < num_of_sectors; count++) {
			strcpy(&(disk[count][phaddr.cyl][phaddr.head][phaddr.sect]), value);

		}

		free(value);
		return 0;
	}
	return -1;
}


bool is_valid(int logical_block_num, int num_of_sects) {

	if ((logical_block_num < 0 || logical_block_num >= MAX_LOGICAL_SECTOR)
	        || (num_of_sects < 0 || num_of_sects > NUM_OF_SECTS)) {

		return false;
	}
	return true;
}

void random_string(char *buffer, int length) {


	char alpha[50] = "abcdefghijklmnopqrstuvwxyz";

	int count;


	for (count = 0; count < (length - 1); ++count) {

		buffer[count] = alpha[random() % 26];
	}
	buffer[length + 1] = '\0';

}


