#include <stdio.h>
#include <stdlib.h>
/*11. Stampare il contenuto di un vettore senza usare indici.*/
#define DIM 6

int main()
{
    int array1[DIM] = {22, 33, 11, 66, 44, 55};
	int * elem = array1;
	int i;
	for (i=0; i<DIM; i++)
		printf("%d ", *(elem++));
	printf("\n");
	return 0;
};

