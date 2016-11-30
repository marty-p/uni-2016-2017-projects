#include <stdio.h>
#include <stdlib.h>
#define DIM 10

void stampa(int * a);

int main()
{
	int v[DIM] = {0};

	printf("Puntatore: %p\n", v);
	stampa(v);

	return 0;
}

void stampa(int * a)
{
	int i;
	for (i = 0; i < DIM; i++, a++)
		printf("%d ", *a);
	printf("\n");
}

