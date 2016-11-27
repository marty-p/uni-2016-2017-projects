#include <stdio.h>
#include <stdlib.h>
/*8. Scrivere una funzione che calcoli il minimo e il massimo presenti in un array e li
"restituisca" utilizzando puntatori.*/
#define DIM 6
int array_minmax(int array[], int dim, int* min, int* max);

int main()
{
    int array[DIM] = {22, 33, 11, 66, 44, 55};
	int min=0, max=0;
	array_minmax(array, DIM, &min, &max);
	printf("min = %d, max = %d\n", min, max);
    return 0;
}

int array_minmax(int array[], int dim, int* min, int* max)
{
	int i;
	int pos_min = 0;
	int pos_max = 0;
	for (i=1; i < dim; i++)
	{
		if (array[i] < array[pos_min])
			pos_min = i;
		if (array[i] > array[pos_max])
			pos_max = i;
	}
	if (min != NULL)
		*min = array[pos_min];
	if (max != NULL)
		*max = array[pos_max];
	return array[pos_min];
}

