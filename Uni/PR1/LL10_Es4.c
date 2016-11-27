#include <stdio.h>
#include <stdlib.h>
/*4. Scrivere una funzione che stampi un vettore. */
#define DIM 6
void printarray(int array[], int dim);

int main()
{
    int array[DIM] = {22, 33, 11, 66, 44, 55};
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

