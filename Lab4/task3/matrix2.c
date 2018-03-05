/**
* Darius Jones
* Lab 4 Task 3
* 2/16/2018
**/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int **a, **b, **c;
int m, k, n;

void *matrixThread(void *cellIndices);
void  allocateAndLoadMatrices(char *fileName);
void loadMatrix(FILE *file, int **m, int rows, int cols);
void multiply(int **a, int **b, int **c, int m, int k, int n);
void displayMatrix(int **m, int rows, int cols);
struct v { int i; int j; } data;
void free_matrx(int **matrix, int rows);
void allocate_matrix(int **matrix, int rows, int cols);

int main(int argc, char **argv) {

	allocateAndLoadMatrices(argv[1]);
	printf("MATRIX A\n");
	displayMatrix(a, m, k);
	printf("MATRIX B\n");
	displayMatrix(b, k, n);
	multiply(a, b, c, m, k, n);
	printf("MATRIX  A x B\n");
	displayMatrix(c, m, n);
	free_matrx(a, m);
	free_matrx(b, k);
	free_matrx(c, n);
	return 0;
}

void *matrixThread(void *cellIndices) {

	struct v *data = cellIndices;
	int counter;
	int sum = 0;
	for (counter = 0; counter < k; counter++) {
		sum += a[data->i][counter] * b[counter][data->j];
	}
	c[data->i][data->j] = sum;
	free(data);
	pthread_exit(0);
}

void allocateAndLoadMatrices(char *fileName) {

	FILE *file_pointer = fopen(fileName, "r");
	if (file_pointer == NULL) {printf("ERROR: file failed to open\n"); exit(EXIT_FAILURE);}
	fscanf(file_pointer, "%d %d %d", &m, &k, &n);
	a = (int**)malloc(m * sizeof(int *));
	b = (int**)malloc(k * sizeof(int *));
	c = (int**)malloc(m * sizeof(int *));
	allocate_matrix(a, m, k);
	allocate_matrix(b, k, n);
	allocate_matrix(c, m, n);
	loadMatrix(file_pointer, a, m, k);
	loadMatrix(file_pointer, b, k, n);
	fclose(file_pointer);
}


void loadMatrix(FILE *file, int **m, int rows, int cols) {

	int col_counter;
	int row_counter;
	for (row_counter = 0; row_counter < rows; row_counter++) {
		for ( col_counter = 0; col_counter < cols; col_counter++) {
			fscanf(file, "%d", &m[row_counter][col_counter]);
		}
	}
}

void multiply(int **a, int **b, int **c, int m, int k, int n) {
	int rc;
	int col_counter;
	int row_counter;
	int tid_counter = 0;
	int num_of_threads = m * n;
	pthread_t tid[num_of_threads];
	struct v *data;


	for (row_counter = 0; row_counter < m; row_counter++) {
		for ( col_counter = 0; col_counter < n; col_counter++) {

			data = (struct v*) malloc(sizeof(struct v));
			pthread_attr_t attr;
			pthread_attr_init(&attr);

			data->i = row_counter;
			data->j = col_counter;

			rc = pthread_create(&tid[tid_counter], &attr, matrixThread, data);
			if (rc) {
				printf("ERROR; return code from pthread_create() is %d\n", rc);
				exit(-1);
			}
			tid_counter++;
		}

	}

	for (tid_counter = 0; tid_counter < num_of_threads; tid_counter++) {
		rc = pthread_join(tid[tid_counter], NULL);

		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}
	}

}

void displayMatrix(int **m, int rows, int cols) {
	int row_counter;
	int col_counter;
	for (row_counter = 0; row_counter < rows; row_counter++) {
		for ( col_counter = 0; col_counter < cols; col_counter++) {
			printf("%d ", m[row_counter][col_counter]);
		}
		printf("\n");
	}
}

void allocate_matrix(int **matrix, int rows, int cols) {
	int count;
	for (count = 0; count < rows; count++) {
		matrix[count] = (int *)malloc(cols * sizeof(int));
	}
}

void free_matrx(int **matrix, int rows) {
	int count;
	for (count = 0; count < rows; count++) {
		free(matrix[count]);
	}
	free(matrix);
}