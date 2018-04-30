/*
* Darius Jones
* Project 2 task 1
* 4/26/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#ifndef _disk_h_ 
#define _disk_h_
#define SECT_SIZE 128
#define NUM_OF_SECTS 32
#define NUM_OF_CYLS 16
#define NUM_OF_HEADS 10
#define MAX_LOGICAL_SECTOR 5120 
#define VALID 0
#define INVALID 1



typedef char sector_t[SECT_SIZE];
typedef sector_t cylinder_t[NUM_OF_SECTS];
typedef cylinder_t head_t[NUM_OF_CYLS];
typedef head_t disk_t[NUM_OF_HEADS];

typedef struct phys_addr {
	int head;
	int cyl;
	int sect;
} physical_address;

disk_t disk;

/**This function translates a logical to a physical address.
https://en.wikipedia.org/wiki/Logical_block_addressing**/
int log_to_phys(int logical_address, physical_address *phys_address);

/**This function translates a physical to a logical address.**/
int phys_to_log(physical_address *phys_address);

/**This function copies num_of_sectors sectors from the disk to the buffer
starting with sector pointed to by logical_block_num. You should validate
the parameters before serving the request.**/
int read(int logical_block_num, int num_of_blocks, void **buffer);

/**This function copies num_of_sectors sectors from the buffer to the disk
starting at sector pointed to by logical_block_num. Here, you also should
validate the parameters.**/
int write(int logical_block_num, int num_of_blocks, void *buffer);

void test();
bool is_valid(int logical_block_num, int num_of_sects);
void random_string(char *buffer, int length);

#endif 