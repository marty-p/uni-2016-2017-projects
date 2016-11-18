#include <stdio.h>
#include <stdlib.h>
/*7. Dichiarare due matrici A e B, inizializzate a piacere, e una terza matrice C che contenga la somma, elemento per elemento,
delle altre due matrici.*/
#include <time.h>
#define DIM1I 10
#define DIM2J 10
#define MIN 0
#define MAX 100
int main()
{
	int A[DIM1I][DIM2J] = {};
	int B[DIM1I][DIM2J] = {};
	int C[DIM1I][DIM2J] = {};
	int i, j;
	srand(time(NULL));

	printf("A:\n");
	for (i=0; i<DIM1I; i++)
	{
		for (j=0; j<DIM2J; j++)
		{
			A[i][j] = MIN + rand() % (MAX - MIN + 1);
			printf("%3d, ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("B:\n");
	for (i=0; i<DIM1I; i++)
	{
		for (j=0; j<DIM2J; j++)
		{
			B[i][j] = MIN + rand() % (MAX - MIN + 1);
			printf("%3d, ", B[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("C:\n");
	for (i=0; i<DIM1I; i++)
	{
		for (j=0; j<DIM2J; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
			printf("%3d, ", C[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

