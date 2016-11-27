#include <stdio.h>
#include <stdlib.h>
/*9. Utilizzare la funzione dell'esercizio precedente per trovare minimo e massimo presenti su ogni riga di
una matrice.*/
#define DIM1 2
#define DIM2 6
int array_minmax(int array[], int dim, int* min, int* max);
void check_matrix_minmax(int matrix[][DIM2], int dim1, int dim2);

int main()
{
    int matrix[DIM1][DIM2] = {
		{11, 22, 33, 44, 55, 66},
		{444, 555, 666, 111, 222, 333},
	};
	check_matrix_minmax(matrix, DIM1, DIM2);
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

void check_matrix_minmax(int matrix[][DIM2], int dim1, int dim2)
{
	int i;
	int min=0, max=0;
	for (i = 0; i<dim1; i++)
	{
		array_minmax(matrix[i], dim2, &min, &max);
		printf("[%d] min = %d, max = %d\n", i, min, max);
	}
}

