/**
* Darius Jones
* Lab 2 Task 1
* 1/30/2018
**/

#include <stdio.h>
#include <stdlib.h>
int offensiveFunc(int, int);

int main(void)
{
	printf("The next line will cause core dump.\n");
	printf("%d\n", offensiveFunc(5.0, 15.0));
	       return 0;
}

int offensiveFunc(int x, int y)
{
	if (y == 0) {
		printf("Divison by zero ERROR, Aborting\n");
		exit(EXIT_FAILURE);
	} else {

		int z = x / y;

		return z;
	}

}
