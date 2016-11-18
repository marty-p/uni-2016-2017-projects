#include <stdio.h>
#include <stdlib.h>
/*Stampare una matrice di float casuali dal primo all’ultimo elemento e
successivamente dall’ultimo al primo.*/
#include <time.h>
#define DIM1I 10
#define DIM2J 10
#define MIN 0.0
#define MAX 100.0
int main()
{
	float matrix[DIM1I][DIM2J] = {};
	int i, j;
	srand(time(NULL));

	for (i=0; i<DIM1I; i++)
	{
		for (j=0; j<DIM2J; j++)
		{
			matrix[i][j] = MIN + ((float)rand() / RAND_MAX) * MAX;
			printf("%6.2f, ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Reverse:\n");
	for (i=DIM1I-1; i>=0; --i)
	{
		for (j=DIM2J-1; j>=0; --j)
		{
			printf("%6.2f, ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

