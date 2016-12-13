#include <stdio.h>
#include <stdlib.h>
/*3. Scrivere una funzione "create_array(int n, int initial_value)" che allochi dinamicamente un array di n
elementi inizializzati a initial_value, e restituisca il puntatore al primo elemento dell'array. */
int * create_array(int n, int initial_value);
#define N 10
int main()
{
	int * pArray = NULL;
	int i;
	pArray = create_array(N, 666);
	for (i=0; i<N; i++)
		printf("%3d ", pArray[i]);
	printf("\n");
	free(pArray);
    return 0;
}

int * create_array(int n, int initial_value)
{
	int * pArray = NULL;
	int i;
	pArray = calloc(n, sizeof(int));
	for (i=0; i<n; i++)
		pArray[i] = initial_value;
	return pArray;
}

