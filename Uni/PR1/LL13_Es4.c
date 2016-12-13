#include <stdio.h>
#include <stdlib.h>
/*4. Scrivere una funzione che calcoli la media degli elementi di un array allocato dinamicamente.
*/
#include <time.h>
int * create_array(int n);
int calcolo_media(int array[], int n);
#define N 10
#define MIN 1
#define MAX 100
int main()
{
	int * pArray = NULL;
	int i;
	srand(time(NULL));
	pArray = create_array(N);
	for (i=0; i<N; i++)
		printf("%3d ", pArray[i]);
	printf("\n");
	printf("media: %d\n", calcolo_media(pArray, N));
	free(pArray);
    return 0;
}

int * create_array(int n)
{
	int * pArray = NULL;
	int i;
	pArray = calloc(n, sizeof(int));
	for (i=0; i<n; i++)
		pArray[i] = MIN + rand() % (MAX - MIN +1);
	return pArray;
}

int calcolo_media(int array[], int n)
{
	int somma = 0;
	int i;
	for (i=0; i<n; i++)
		somma += array[i];
	return somma/n;
}

