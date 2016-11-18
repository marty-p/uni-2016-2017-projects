#include <stdio.h>
#include <stdlib.h>
/*4. Generare una matrice identità (1 sulla diagonale principale, i restanti valori a 0) utilizzando un solo ciclo for.*/
#include <time.h>
#define DIM1I 9
#define DIM2J 9
#define MIN 0
#define MAX 100
int main()
{
	int matrix[DIM1I][DIM2J] = {};
	int i, j;
	srand(time(NULL));

	// diagonale (modo 1)
	for (i=0; i<DIM1I; i++)
		matrix[i][i] = 1;

	// diagonale inversa (modo 1)
	for (i=0; i<DIM1I; i++)
		matrix[i][DIM1I-i-1] = 1;

	for (i=0; i<DIM1I; i++)
	{
		for (j=0; j<DIM2J; j++)
		{
			// diagonale (modo 2)
			if (i==j)
				matrix[i][j] = 1;
			// diagonale inversa (modo 2)
			if (i==DIM2J-j-1)
				matrix[i][j] = 1;

			printf("%d, ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

