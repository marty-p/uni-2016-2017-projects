#include <stdio.h>
#include <stdlib.h>
/*Stampare una matrice di interi casuali dal primo all’ultimo elemento e
successivamente dall’ultimo al primo.*/
#include <time.h>
#define DIM1I 10
#define DIM2J 10
#define MIN 0
#define MAX 100
int main()
{
	int matrix[DIM1I][DIM2J] = {};
	int i, j;
	srand(time(NULL));

	for (i=0; i<DIM1I; i++)
	{
		for (j=0; j<DIM2J; j++)
		{
			matrix[i][j] = MIN + rand() % (MAX - MIN + 1);
			printf("%3d, ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Reverse:\n");
	for (i=DIM1I-1; i>=0; --i)
	{
		for (j=DIM2J-1; j>=0; --j)
		{
			printf("%3d, ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

