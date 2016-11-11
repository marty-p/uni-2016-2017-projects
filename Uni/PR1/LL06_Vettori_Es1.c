#include <stdio.h>
#include <stdlib.h>
/*1. Generare una serie di N numeri all'interno di un array, dopodiché stampare la serie di numeri invertita.
*/
#include <time.h>
#define N 10
#define MIN 1
#define MAX 100

int main()
{
	int array[N];
	int i;

	srand(time(NULL));

	for (i=0; i < N; i++)
	{
		array[i] = MIN + rand() % (MAX - MIN + 1);
		printf("%d ", array[i]);
	}
	printf("\n");

	printf("Invertita:\n");
	for (i=N-1; 0 <= i; i--)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}

