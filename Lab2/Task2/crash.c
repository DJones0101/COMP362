/**
* Darius Jones
* Lab 2 Task 2
* 1/31/2018
**/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *getStrToPrint(char *);
char *ptr;

#define STR_BOYS "Boys!"
#define STR_GIRLS "Girls!"

int main(void)
{
	printf("To the boys: %s\n", getStrToPrint(STR_BOYS));
	free(ptr); 
	printf("To the girls: %s\n", getStrToPrint(STR_GIRLS));
	free(ptr);
}

char *getStrToPrint(char *to)
{

	// When using sprintf the ptr needs to malloced.
	ptr = malloc(sizeof(char) * 256);
	sprintf(ptr, "Hello %s!", to);
	return ptr;
}
