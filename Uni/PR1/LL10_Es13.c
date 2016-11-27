#include <stdio.h>
#include <stdlib.h>
/*13. Scrivere un programma in cui è dichiarato un vettore v, di dimensione N. Il vettore deve essere
popolato con numeri interi, positivi e negativi, generati casualmente. Scrivere poi una funzione che riceve
come parametro il vettore e inverte l' ordine degli elementi. Visualizzare dal main sia il vettore originale
che quello ottenuto dopo la chiamata della funzione.*/
#include <time.h>
#define N 20
#define MIN -100
#define MAX +100

void reverse_array(int array[], int n);

int main()
{
    int array[N] = {};
	int i;
	srand(time(NULL));
	for (i=0; i<N; i++)
	{
		array[i] = MIN + rand() % (MAX - MIN + 1);
		printf("%d ", array[i]);
	}
	printf("\n");

	reverse_array(array, N);
	for (i=0; i<N; i++)
		printf("%d ", array[i]);
	printf("\n");

	return 0;
};

void reverse_array(int array[], int n)
{
	int temp;
	int i;
	for (i=0; i<(n/2); i++)
	{
		temp = array[i];
		array[i] = array[n-i-1];
		array[n-i-1] = temp;
	}
}

