/*
* Darius Jones
* Project 2 task 3
* 5/5/2018
*/

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/fs.h>
//#include <asm/uaccess.h> // Ubuntu 16.xx
#include <linux/uaccess.h> // Ubuntu 17.10+

#include "sim_dev.h"

// arbitrary number
#define SIM_DEV_MAJOR 567
#define SIM_DEV_NAME "sim_dev"

// this space holds the data that device users send to the device
static char *storage = NULL;

#define STORAGE_SIZE 4096

static unsigned long ioctl_control_data;
static unsigned long ioctl_status_data;
static REGISTER *disk_status = (REGISTER *) &ioctl_status_data;
static REGISTER *disk_control = (REGISTER *) &ioctl_control_data;


static int is_valid(REGISTER *reg) {
	if (!reg->ready) {
		printk(KERN_DEFAULT "not ready");
		reg->error_code = E_RDY;
		return E_RDY;
	}
	if (reg->cyl >= NUM_OF_CYLS) {
		printk(KERN_DEFAULT "Invalid cyl\n");
		reg->error_code = E_CYL;
		return E_CYL;
	}
	if (reg->head >= NUM_OF_HEADS) {
		printk(KERN_DEFAULT "Invalid head\n");
		reg->error_code = E_HEAD;
		return E_HEAD;
	}
	if (reg->sect >= NUM_OF_SECTS) {
		printk(KERN_DEFAULT "Invalid sect\n");
		reg->error_code = E_HEAD;
		return E_HEAD;
	}
	if (reg->sector_count == 0 || reg->sector_count >= NUM_OF_SECTS) {
		reg->error_code = E_SECTCOUNT;
		printk(KERN_DEFAULT "Invalid sector count\n");
		return E_SECTCOUNT;
	}
	return 0;
}


// open function - called when the "file" /dev/sim_dev is opened in userspace
static int sim_dev_open (struct inode *inode, struct file *file) {
	// this is a special print functions that allows a user to print from the kernel
	printk("sim_dev_open\n");
	return 0;
}

// close function - called when the "file" /dev/sim_dev is closed in userspace
static int sim_dev_release (struct inode *inode, struct file *file) {
	printk("sim_dev_release\n");
	return 0;
}

// read function called when  /dev/sim_dev is read
static ssize_t sim_dev_read( struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {

	int sector;
	int buffer_index;
	int sector_index;
	int sect;
	int valid_address = is_valid(disk_control);
	printk(KERN_DEFAULT "TEST sim_dev_read: cyl = %d. head = %d. sect = %d. sector_count = %d\n",
	       disk_control->cyl, disk_control->head, disk_control->sect, disk_control->sector_count);

	if (valid_address != 0)
		return valid_address;

	storage = kmalloc(SECT_SIZE * disk_control->sector_count, GFP_KERNEL);
	sector = 0;
	buffer_index = 0;
	sector_index = 0;
	sect = disk_control->sect;
	while (sector < disk_control->sector_count) {
		for (sector_index = 0; sector_index < SECT_SIZE; sector_index++) {
			if (disk[disk_control->cyl][disk_control->head][sect][sector_index] == '\0') {
				break;
			}
			storage[buffer_index] = disk[disk_control->cyl][disk_control->head][sect][sector_index];
			buffer_index++;
		}
		sector++;
		sect = (sect + 1) % NUM_OF_SECTS;
	}
	storage[buffer_index] = '\0';

	printk(KERN_DEFAULT "READ \"%s\"\n", storage);

	if (copy_to_user(buf, storage, count) != 0) {
		disk_status->error_code = -EFAULT;
		kfree(storage);
		storage = NULL;
		return -EFAULT;
	}
	kfree(storage);
	storage = NULL;

	disk_status->ready = 1;
	disk_status->error_code = 0;
	return 0;
}

// write function called when /dev/sim_dev is written to
static ssize_t sim_dev_write( struct file *filp, const char __user *buf, size_t count, loff_t *f_pos) {

	int sector_index;
	int buffer_index;
	int sect;
	int sector;

	int valid_address = is_valid(disk_control);
	printk(KERN_DEFAULT "sim_dev_write: cyl = %d. head = %d. sect = %d. sector_count = %d\n",
	       disk_control->cyl, disk_control->head, disk_control->sect, disk_control->sector_count);

	if (valid_address != 0)
		return valid_address;

	sector_index = 0;
	buffer_index = 0;
	sect = disk_control->sect;
	sector = 0;

	while (sector < disk_control->sector_count) {
		for (sector_index = 0; sector_index < SECT_SIZE; sector_index++) {
			disk[disk_control->cyl][disk_control->head][sect][sector_index] = ((char *)buf)[buffer_index];
			if (((char *)buf)[buffer_index] == '\0') {
				buffer_index++;
				break;
			}
			buffer_index++;
		}
		sector++;
		sect = (sect + 1) % NUM_OF_SECTS;
	}
	printk(KERN_DEFAULT "write \"%s\"\n", disk[disk_control->cyl][disk_control->head][disk_control->sect]);

	disk_control->ready = 1;
	disk_control->error_code = 0;
	return 0;
}


// ioctl function called when /dev/sim_dev receives an ioctl command
// Ubuntu 10.10: static int sim_dev_ioctl(struct inode *inode, struct file *file, unsigned int command, unsigned long arg)
// Ubuntu 11.04:
static long sim_dev_unlocked_ioctl(struct file *file, unsigned int command, unsigned long arg) {
	int *p;
	switch ( command ) {
	case IOCTL_SIM_DEV_WRITE:/* for writing data to arg */
		p = (int *)arg;
		printk(KERN_DEFAULT "IOTCTL: Setting control reg to %d\n", *p);
		if (copy_from_user(&ioctl_control_data, (int *)arg, sizeof(int)))
			return -EFAULT;
		break;

	case IOCTL_SIM_DEV_READ:/* for reading data from arg */
		if (copy_to_user((int *)arg, &ioctl_status_data, sizeof(int)))
			return -EFAULT;
		break;

	default:
		return -EINVAL;
	}
	return -EINVAL;
}

//
// mapping of file operations to the driver functions
//
struct file_operations sim_dev_file_operations = {
	.owner	=	THIS_MODULE,
	.llseek	=	NULL,
	.read		=	sim_dev_read,
	.write	=	sim_dev_write,
//	.readdir	=	NULL, // Ubuntu 14.04
	.poll		=	NULL,
//	.ioctl	=	sim_dev_ioctl, // Ubuntu 10.10
	.unlocked_ioctl	=	sim_dev_unlocked_ioctl, // Ubuntu 11.04
	.mmap		=	NULL,
	.open		=	sim_dev_open,
	.flush	=	NULL,
	.release	=	sim_dev_release,
	.fsync	=	NULL,
	.fasync	=	NULL,
	.lock		=	NULL,
};

// Loads a module in the kernel
static int sim_dev_init_module (void) {
	// here we register sim_dev as a character device
	if (register_chrdev(SIM_DEV_MAJOR, SIM_DEV_NAME, &sim_dev_file_operations) != 0)
		return -EIO;

	// reserve memory with kmalloc - Allocating Memory in the Kernel
	// GFP_KERNEL --> this does not have to be atomic, so kernel can sleep
	storage = kmalloc(STORAGE_SIZE, GFP_KERNEL);
	if (!storage) {
		printk(KERN_INFO "kmalloc failed\n");
		return -1;
	}
	printk(KERN_INFO "Simulated Driver Module Installed\n");
	return 0;
}

//  Removes module from kernel
static void sim_dev_cleanup_module(void) {
	// specialized function to free memeory in kernel
	kfree(storage);
	unregister_chrdev (SIM_DEV_MAJOR, SIM_DEV_NAME);
	printk(KERN_INFO"Simulated Driver Module Uninstalled\n");
}




// map the module initialization and cleanup functins
module_init(sim_dev_init_module);
module_exit(sim_dev_cleanup_module);

MODULE_AUTHOR("http://www.cs.csuci.edu/~ajbieszczad");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simulated Device Linux Device Driver");