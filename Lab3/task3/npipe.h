/**
* Darius Jones
* Lab 3 Task 3
* 2/8/2018
**/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 1024
#define	oops(m,x)	{ perror(m); exit(x); }

