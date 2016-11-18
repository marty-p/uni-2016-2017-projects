#include <stdio.h>
#include <stdlib.h>
/*3. Dichiarare una matrice NxM di valori casuali, stampare la matrice e successivamente stampare la somma di tutti i valori
contenuti.*/
#include <time.h>
#define DIM1I 10
#define DIM2J 10
#define MIN 0
#define MAX 100
int main()
{
	int matrix[DIM1I][DIM2J] = {};
	int i, j;
	int somma=0;
	srand(time(NULL));
	for (i=0; i<DIM1I; i++)
	{
		for (j=0; j<DIM2J; j++)
		{
			matrix[i][j] = MIN + rand() % (MAX - MIN + 1);
			somma += matrix[i][j];
			printf("%d, ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Somma: %d\n", somma);
	return 0;
}

