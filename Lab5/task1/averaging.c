/**
* Darius Jones
* Lab 5 Task 1
* 2/22/2018
**/

#include <stdio.h>
#include <stdlib.h>

double current, past, alpha;
int previous_run, counter = 0;

int main(int argc, char *argv[]) {

	printf("Please enter alpha value:\n");
	fscanf(stdin, "%lf", &alpha);

	while (1) {
		if(fscanf(stdin, "%d", &previous_run) == EOF){break;}
		if (current == 0) { past = previous_run;}
		current = (alpha * previous_run) + ((1 - alpha) * past);
		past = current;
		printf("Burst %d is: %d\n", counter, previous_run);
		printf("Tau %d is: %.2lf\n", counter, current);
		counter++;
	}

	return 0;
}