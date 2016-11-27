#include <stdio.h>
#include <stdlib.h>
/*3. Scrivere una funzione che, preso in ingresso un array, ne restituisca il valore minimo.
Scrivere altre due funzioni per il calcolo del massimo e della media.*/
#define DIM 6
int array_min(int array[], int dim);
int array_max(int array[], int dim);
int array_avg(int array[], int dim);

int main()
{
    int array[DIM] = {22, 33, 11, 66, 44, 55};
	int min, max, avg;
	min = array_min(array, DIM);
	max = array_max(array, DIM);
	avg = array_avg(array, DIM);
	printf("min = %d, max = %d, avg = %d\n", min, max, avg);
    return 0;
}

int array_min(int array[], int dim)
{
	int i;
	int pos_min = 0;
	for (i=1; i < dim; i++)
		if (array[i] < array[pos_min])
			pos_min = i;
	return array[pos_min];
}

int array_max(int array[], int dim)
{
	int i;
	int pos_max = 0;
	for (i=1; i < dim; i++)
		if (array[i] > array[pos_max])
			pos_max = i;
	return array[pos_max];
}

int array_avg(int array[], int dim)
{
	int i;
	int sum = 0;
	for (i=0; i < dim; i++)
		sum += array[i];
	return sum / dim;
}

