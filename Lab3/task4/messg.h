/*
 *  messg.h
 *  lab4
 *
 *  Created by AJ Bieszczad on 2/9/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 */

#ifndef _MESSG_H
#define _MESSG_H

#include	<sys/types.h>
#include	<stdio.h>
#include	<stdlib.h>
//#include	<string.h>
//#include	<unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <math.h>


#define TRUE 1

#define DEFAULT_PRIORITY 1

#define SRV_PORT 1234

typedef int STAT;

typedef struct messg {
	long priority;
	key_t sender;
	float num;
} MESSG;

#define oops(m,x)  { perror(m); exit(x); }

#endif