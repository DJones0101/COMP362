/**
* Darius Jones
* Lab 4 Task 4
* 2/16/2018
**/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *matrixThread(void *matrixCell);
void allocateAndLoadMatrices(char *fileName, int ***a, int ***b, int ***c, int *m, int *k, int *n);
void loadMatrix(FILE *file, int ***matrix, int rows, int cols);
pthread_t **alloc_tids(int rows, int cols);
void free_tids(pthread_t **threads, int rows);
pthread_t **multiply(int **a, int **b, int **c, int m, int k, int n);
void displayMatrix(int **matrix, int rows, int cols);
void free_matrix(int **matrix, int rows);
int **allocate_matrix(int *rows, int *cols);

struct matrixCell
{
	int i;
	int j;
	int k;
	int **a;
	int **b;
	int **c;
};

int main(int argc, char *argv[])
{
	int **a, **b, **c; // matrices
	int m, k, n; // dimensions of the matrices m x k and k x n

	allocateAndLoadMatrices(argv[1], &a, &b, &c, &m, &k, &n);
	printf("MATRIX A\n");
	displayMatrix(a, m, k);
	printf("MATRIX B\n");
	displayMatrix(b, k, n);
	multiply(a, b, c, m, k, n);
	printf("MATRIX  A x B\n");
	displayMatrix(c, m, n);
	free_matrix(a, m);
	free_matrix(b, k);
	free_matrix(c, m);
	return 0;
}

void *matrixThread(void *matrixCell) {

	struct matrixCell *data = matrixCell;
	int counter;
	int sum = 0;
	for (counter = 0; counter < data->k; counter++) {
		sum += data->a[data->i][counter] * data->b[counter][data->j];
	}
	data->c[data->i][data->j] = sum;
	free(data);
	pthread_exit(0);
}

void allocateAndLoadMatrices(char *fileName, int ***a, int ***b, int ***c, int *m, int *k, int *n) {
	int count;
	FILE *file_pointer = fopen(fileName, "r");
	if (file_pointer == NULL) {printf("ERROR: file failed to open\n"); exit(EXIT_FAILURE);}
	fscanf(file_pointer, "%d %d %d", m, k, n);
	// note to self: printf("%d %d %d\n", *m, *k, *n ); <- works;
	*a = allocate_matrix(m, k);
	*b = allocate_matrix(k, n);
	*c = allocate_matrix(m, n);
	loadMatrix(file_pointer, a, *m, *k);
	loadMatrix(file_pointer, b, *k, *n);
	fclose(file_pointer);
}


void loadMatrix(FILE *file, int ***matrix, int rows, int cols) {
	int col_counter;
	int row_counter;
	for (row_counter = 0; row_counter < rows; row_counter++) {
		for ( col_counter = 0; col_counter < cols; col_counter++) {
			fscanf(file, "%d", &matrix[0][row_counter][col_counter]);
		}
	}
}

pthread_t **multiply(int **a, int **b, int **c, int m, int k, int n) {

	int rc;
	int col_counter;
	int row_counter;
	int num_of_threads = m * n;
	pthread_t **tid = alloc_tids(m, n);
	struct matrixCell *data;

	for (row_counter = 0; row_counter < m; row_counter++) {
		for ( col_counter = 0; col_counter < n; col_counter++) {

			data = (struct matrixCell*) malloc(sizeof(struct matrixCell));
			pthread_attr_t attr;
			pthread_attr_init(&attr);

			data->i = row_counter;
			data->j = col_counter;
			data->a = a;
			data->b = b;
			data->c = c;
			data->k = k;

			rc = pthread_create(&tid[row_counter][col_counter], &attr, matrixThread, data);
			if (rc) {
				printf("ERROR; return code from pthread_create() is %d\n", rc);
				exit(-1);
			}

		}

	}

	for (row_counter = 0; row_counter < m; row_counter++) {
		for ( col_counter = 0; col_counter < n; col_counter++) {

			rc = pthread_join(tid[row_counter][col_counter], NULL);
			if (rc) {
				printf("ERROR; return code from pthread_join() is %d\n", rc);
				exit(-1);
			}
		}
	}

	c = data->c;
	free_tids(tid, n);
}

void displayMatrix(int **matrix, int rows, int cols) {
	int row_counter;
	int col_counter;
	for (row_counter = 0; row_counter < rows; row_counter++) {
		for ( col_counter = 0; col_counter < cols; col_counter++) {
			printf("%d ", matrix[row_counter][col_counter]);
		}
		printf("\n");
	}

}

int **allocate_matrix(int *rows, int *cols) {

	int **matrix = malloc(*rows * sizeof(int *));
	int count;
	for (count = 0; count < *rows; count++) {
		matrix[count] = (int *)malloc(*cols * sizeof(int));
	}
	return matrix;
}

void free_matrix(int **matrix, int rows) {
	int count;
	for (count = 0; count < rows; count++) {
		free(matrix[count]);
	}
	free(matrix);
}

pthread_t **alloc_tids(int rows, int cols) {
	pthread_t **tids = malloc(rows * sizeof(int *));
	int col_counter;
	for (col_counter = 0; col_counter < rows; col_counter++) {

		tids[col_counter] = malloc(sizeof(int));
	}
	return tids;
}
void free_tids(pthread_t **threads, int rows) {
	int row_counter;
	for (row_counter = 0; row_counter < rows; row_counter++) {
		free(threads[row_counter]);
	}
	free(threads);

}