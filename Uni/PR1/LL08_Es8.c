#include <stdio.h>
#include <stdlib.h>
/*8. Date due matrici Casuali A (LxM) e B (MxN), calcolare il prodotto righe per colonne C=AxB (la matrice risultante C avrà
dimensione LxN). Ogni elemento c[i][j] è calcolato nel seguente modo:
c[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + ... + a[i][M-1]*b[M-1][j]
(vedi: http://it.wikipedia.org/wiki/Moltiplicazione_di_matrici)*/
#include <time.h>
#define L 10
#define M 10
#define N 10
#define MIN 0
#define MAX 100
int main()
{
	int A[L][M] = {};
	int B[M][N] = {};
	int C[L][N] = {};
	int i, j, k;
	srand(time(NULL));

	printf("A:\n");
	for (i=0; i<L; i++)
	{
		for (j=0; j<M; j++)
		{
			A[i][j] = MIN + rand() % (MAX - MIN + 1);
			printf("%3d, ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("B:\n");
	for (i=0; i<M; i++)
	{
		for (j=0; j<N; j++)
		{
			B[i][j] = MIN + rand() % (MAX - MIN + 1);
			printf("%3d, ", B[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("C:\n");
	for (i=0; i<L; i++)
	{
		for (j=0; j<N; j++)
		{
			for (k=0; k<M; k++)
				C[i][j] += A[i][k]*B[k][j];
			printf("%5d, ", C[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

