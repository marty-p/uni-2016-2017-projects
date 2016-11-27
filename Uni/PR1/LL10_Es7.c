#include <stdio.h>
#include <stdlib.h>
/*7. Scrivere una funzione che controlli se due vettori sono uguali.*/
#include <stdbool.h>
#define DIM 6
_Bool checkarray(int array1[], int array2[], int dim);
int main()
{
    int array1[DIM] = {22, 33, 11, 66, 44, 55};
    int array2[DIM] = {22, 33, 11, 66, 44, 55};
    int array3[DIM] = {666, 666, 666, 666, 666, 666};
	printf("array1==array2 = %d\n", checkarray(array1, array2, DIM));
	printf("array2==array3 = %d\n", checkarray(array2, array3, DIM));
	return 0;
};

_Bool checkarray(int array1[], int array2[], int dim)
{
	_Bool same = true;
	int i=0;
	for (i=0; i<dim && same==true; i++)
		if (array1[i]!=array2[i])
			same = false;
	return same;
}

