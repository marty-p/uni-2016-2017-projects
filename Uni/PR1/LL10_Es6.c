#include <stdio.h>
#include <stdlib.h>
/*6. Scrivere una funzione che inizializzi un vettore ad un dato valore.*/
#define DIM 6
void printarray(int array[], int dim);
void initarray(int array[], int dim, int value);

int main()
{
    int array[DIM] = {};
	initarray(array, DIM, 666);
	printarray(array, DIM);
	return 0;
};

void printarray(int array[], int dim)
{
	int i;
	for (i=0; i < dim; i++)
		printf("%d ", array[i]);
	printf("\n");
}

void initarray(int array[], int dim, int value)
{
	int i;
	for (i=0; i < dim; i++)
		array[i] = 666;
}

