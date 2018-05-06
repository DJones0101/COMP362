/*
* Darius Jones
* Project 2 task 4
* 5/5/2018
*/

#ifndef __SIM_DEV_H_
#define __SIM_DEV_H_

#define IOCTL_SIM_DEV_WRITE _IOR(0, 1, int)
#define IOCTL_SIM_DEV_READ _IOR(0, 2, int)
#include <linux/errno.h>


#define E_CYL 1
#define E_HEAD 2
#define E_SECT 3
#define E_SECTCOUNT 4
#define E_RDY 5

#define SECT_SIZE 128
#define NUM_OF_SECTS 32
#define NUM_OF_CYLS 16
#define NUM_OF_HEADS 10
#define MAX_LOGICAL_SECTOR 5

typedef char sect_t[SECT_SIZE];
typedef sect_t head_t[NUM_OF_SECTS];
typedef head_t cylinder_t[NUM_OF_HEADS];
typedef cylinder_t disk_t[NUM_OF_CYLS];

disk_t disk;

typedef struct{
  int cyl;
  int head;
  int sect;
} physaddr_t;

typedef struct {
     unsigned ready:1;
     unsigned error_code:7;
     unsigned cyl:8;
     unsigned head:4;
     unsigned sect:7;
     unsigned sector_count:5;
}REGISTER;

//static int is_valid(REGISTER *reg); 
int log_to_phys(int logaddr, physaddr_t *phaddr);
void error_code(int ret_val);
//static ssize_t sim_dev_write( struct file *filp, const char __user *buf, size_t count, loff_t *f_pos);
//static ssize_t sim_dev_read( struct file *filp, char __user *buf, size_t count, loff_t *f_pos);
void random_string(char *buffer, int length);

#endif