#include <stdio.h>
#include <stdlib.h>
/*Dichiarare un vettore di 5 elementi. Assegnare casualmente i valori da 1 a 90 senza
ripetizioni.*/
#include <time.h>
#include <stdbool.h>
#define N 5
#define MIN 1
#define MAX 90

int main()
{
	int array[N] = {};
	_Bool ripetizioni[MAX - MIN] = {};
	int i;

	srand(time(NULL));

	for (i=0; i<N; i++)
	{
		do {
			array[i] = MIN + rand() % (MAX - MIN + 1);
		} while (ripetizioni[array[i] - MIN] == true);
		ripetizioni[array[i] - MIN] = true;
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}

