#include <stdio.h>
#include <stdlib.h>
/*4. Dichiarare e inizializzare un array in modo che contenga le potenze di 2 da 2^0 fino a 2^(N-1).
*/
#include <math.h>
#define N 8

int main()
{
	int array[N];
	int i;
	for (i=0; i < N; i++)
	{
		array[i] = pow(2, i);
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}

