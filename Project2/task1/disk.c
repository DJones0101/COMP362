/*
* Darius Jones
* Project 2 task 1
* 4/26/2018
*/

#include <stdio.h>
#include "disk.h"


int log_to_phys(int logical_address, physical_address *phys_address){


  /*C = LBA ÷ (HPC × SPT)
    H = (LBA ÷ SPT) mod HPC
    S = (LBA mod SPT) + 1*/

	phys_address->cyl = logical_address / (NUM_OF_CYLS * NUM_OF_SECTS);
	phys_address->head = (logical_address / NUM_OF_SECTS) % NUM_OF_HEADS ;
	phys_address->sect = (logical_address % NUM_OF_SECTS) + 1;

	// valid range 0 to MAX_LOGICAL_SECTOR
	 return ((logical_address >= 0 ) && (logical_address <= MAX_LOGICAL_SECTOR))?  0 : 1;

}

int phys_to_log(physical_address *phys_address){

	/*LBA = (C × HPC + H) × SPT + (S - 1)*/
	return (phys_address->cyl * NUM_OF_CYLS + phys_address->head) *  NUM_OF_SECTS + (phys_address->sect - 1);

}

int read(int logical_block_num, int num_of_blocks, void **buffer){

}

int write(int logical_block_num, int num_of_sectors, void *buffer){

}