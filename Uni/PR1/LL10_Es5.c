#include <stdio.h>
#include <stdlib.h>
/*5. Scrivere una funzione che stampi una matrice (che richiama la funzione scritta per
l'esercizio 4).*/
#define DIM1 2
#define DIM2 6
void printarray(int array[], int dim);
void printmatrix(int matrix[][DIM2], int dim1, int dim2);

int main()
{
    int matrix[DIM1][DIM2] = {
		{11, 22, 33, 44, 55, 66},
		{77, 88, 99, 111, 222, 333},
	};
	printmatrix(matrix, DIM1, DIM2);
	return 0;
};

void printarray(int array[], int dim)
{
	int i;
	for (i=0; i < dim; i++)
		printf("%d ", array[i]);
	printf("\n");
}

void printmatrix(int matrix[][DIM2], int dim1, int dim2)
{
	int i;
	for (i=0; i < dim1; i++)
		printarray(matrix[i], dim2);
}

