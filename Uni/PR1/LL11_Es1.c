#include <stdio.h>
#include <stdlib.h>
/*1. Implementare una struttura vector2D composta da due componenti x e y. Implementare una
funzione per la somma e il prodotto, componente per componente, di due vettori.
Implementare successivamente una struttura e le relative operazioni che gestisce un
vector3D*/
#define N 5

typedef struct vector2D_s {
	int x;
	int y;
} vector2D;

typedef struct vector3D_s {
	int x;
	int y;
	int z;
} vector3D;

int sum_2d(vector2D a1[], vector2D a2[], int n);

int main()
{
	vector2D array1[N] = {{11, 22},{11, 22},{11, 22},{11, 22},{11, 22},};
	vector2D array2[N] = {{33, 44},{55, 66},{77, 88},{99, 00},{111, 122},};
	int i;
	int somma = 0;
	for (i=0; i<N; i++)
	{
		sum_2d(array1[i], array2[i]);
	}
	return 0;
}

int sum_2d(vector2D * a1, vector2D * a2)
{
	return a1.x + a2.x
}
