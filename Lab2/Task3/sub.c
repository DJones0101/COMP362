
/**
* Darius Jones
* Lab 2 Task 3
* 2/2/2018
**/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void print_usage_error(int);

#define USAGE 1
#define FAILURE_TO_OPEN 2

FILE *input_file;
FILE *output_file;

int main(int argc, char **argv) {
	char replaced_char;
	char replacement_char;
// SECTION 1:
// Setting up replaced_char and replacement_char
// Check that there are at least the minimum number of arguments

	if (argc >= 3) {

// Get replaced_char and replacement_char from argv.



		replaced_char = argv[1][0];
		replacement_char = argv[2][0];

//SECTION 2:
// Process the remaining arguments (if any)
// Use a while loop to process any input or output file arguments using freopen.
// Be sure to check whether freopen was successful.


		int current_arrguement = 0;

		while (current_arrguement < argc ) {

			if (strcmp(argv[current_arrguement], "-f") == 0) {  // (-f found ) processing input argument

				current_arrguement++;

				if (argv[current_arrguement] == NULL) {
					print_usage_error(USAGE);
				} else {

					input_file = freopen(argv[current_arrguement], "r", stdin);

					if (input_file == NULL) {

						print_usage_error(FAILURE_TO_OPEN);
					}
				}
			}


			if (strcmp(argv[current_arrguement], "-o") == 0) {  // (-o found ) processing output argument

				current_arrguement++;


				if (argv[current_arrguement] == NULL) {
					print_usage_error(USAGE);
				} else {

					output_file = freopen(argv[current_arrguement], "w", stdout);

					if (output_file == NULL) {

						print_usage_error(FAILURE_TO_OPEN);
					}
				}

			}

			current_arrguement++;
		}



	} else {
// Otherwise print the usage.

		print_usage_error(USAGE);


	}

// SECTION 3:
// Use a while loop to process the entire input stream and perform the main substitution functionality.

	char current_char = fgetc(stdin);



	if (input_file == NULL) { // reading from the terminal

		while (current_char != EOF && current_char != '\n') {

			if (current_char == replaced_char) {
				current_char = replacement_char;
			}

			printf("%c", current_char);

			current_char = fgetc(stdin);


		}

		printf("\n");

	} else {

		while (current_char != EOF) { // reading from a file

			if (current_char == replaced_char) {
				current_char = replacement_char;
			}

			printf("%c", current_char);

			current_char = fgetc(stdin);


		}
		printf("\n");

	}

// SECTION 4:
// Close the input and output streams.

	if (input_file) {fclose(input_file);}
	if (output_file) {fclose(output_file);}
}

void print_usage_error(int code) {

	switch (code) {

	case 1: printf("sub replaced_char replacement_char [-f input_file] [-o output_file]\n");
		break;
	case 2:	printf("Error: file [] not opened\n");
		break;
	}

	exit(EXIT_FAILURE);
}

