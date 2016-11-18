#include <stdio.h>
#include <stdlib.h>
/*6. Dichiarare due matrici A e B. Dopo aver inizializzato A a piacimento, fare in modo che la matrice B sia la matrice trasposta
di A.*/
#include <time.h>
#define DIM1I 10
#define DIM2J 10
#define MIN 0
#define MAX 100
int main()
{
	int A[DIM1I][DIM2J] = {};
	int B[DIM1I][DIM2J] = {};
	int i, j;
	srand(time(NULL));
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

	printf("B trasposta di A:\n");
	for (i=0; i<DIM1I; i++)
	{
		for (j=0; j<DIM2J; j++)
		{
			B[i][j] = A[j][i];
			printf("%3d, ", B[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

