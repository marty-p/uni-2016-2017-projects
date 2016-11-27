#include <stdio.h>
#include <stdlib.h>
/*10. Scrivere una funzione di ricerca di un elemento di un array. Se l'elemento passato come parametro si
trova nell'array la funzione ne restituisce l'indice di posizione, altrimenti restituisce -1. */
#include <stdbool.h>
#define DIM 6
_Bool search_in_array(int array[], int dim, int value);

int main()
{
    int array1[DIM] = {22, 33, 11, 66, 44, 55};
    int array2[DIM] = {666, 666, 666, 666, 666, 666};
	int value = 66;
	printf("%d in array1 = %d\n", value, search_in_array(array1, DIM, value));
	printf("%d in array2 = %d\n", value, search_in_array(array2, DIM, value));
	return 0;
};

_Bool search_in_array(int array[], int dim, int value)
{
	_Bool found = false;
	int i=0;
	for (i=0; i<dim && found==false; i++)
		if (array[i] == value)
			found = true;
	return found;
}

