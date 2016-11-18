#include <stdio.h>
#include <stdlib.h>
/*5. Generare casualmente una matrice NxM. Dichiarare un array R di N elementi e un array C di M elementi. Salvare in R[i] la
somma degli elementi della riga i-esima della matrice, e in C[j] la somma degli elementi della colonna j-esima della matrice.*/
#include <time.h>
#define N 10
#define M 10
#define MIN 0
#define MAX 100
int main()
{
	int NxM[N][M] = {};
	int i, j;
	int R[N] = {};
	int C[M] = {};
	srand(time(NULL));

	for (i=0; i<N; i++)
	{
		for (j=0; j<M; j++)
		{
			NxM[i][j] = MIN + rand() % (MAX - MIN + 1);
			printf("%d, ", NxM[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("R:\n");
	for (i=0; i<N; i++)
	{
		for (j=0; j<M; j++)
			R[i] += NxM[i][j];
		printf("%d, ", R[i]);
	}
	printf("\n");

	printf("C:\n");
	for (j=0; j<M; j++)
	{
		for (i=0; i<N; i++)
			C[j] += NxM[i][j];
		printf("%d, ", C[j]);
	}
	printf("\n");

	return 0;
}

