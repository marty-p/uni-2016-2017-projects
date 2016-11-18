#include <stdio.h>
#include <stdlib.h>
/*Generata casualmente una matrice con numeri interi tra 0 e 100, far inserire
all’utente una coppia di indici e decrementare il valore della relativa cella di 10 unità.
Decrementare anche il valore delle celle adiacenti di 5 unità.*/
#include <time.h>
#define DIM1I 10
#define DIM2J 10
#define MIN 0
#define MAX 100
#define CELLA_PROPRIA_DEC_VALUE 10
#define CELLA_ADIACENTE_DEC_VALUE 5
int main()
{
	int matrix[DIM1I][DIM2J] = {};
	int i, j;
	int inputI, inputJ;
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

	do {
		printf("Immetti un indice i tra %d e %d:\n", 0, DIM1I-1);
		scanf("%d", &inputI);
	} while (inputI < 0 || inputI >= DIM1I);

	do {
		printf("Immetti un indice j tra %d e %d:\n", 0, DIM2J-1);
		scanf("%d", &inputJ);
	} while (inputJ < 0 || inputJ >= DIM2J);

	for (i=0; i<DIM1I; i++)
	{
		for (j=0; j<DIM2J; j++)
		{
			if (inputI==i)
			{
				matrix[i][j] -= (inputJ==j) ? CELLA_PROPRIA_DEC_VALUE : CELLA_ADIACENTE_DEC_VALUE;
			}
			printf("%3d, ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

