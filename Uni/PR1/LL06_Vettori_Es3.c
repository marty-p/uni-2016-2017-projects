#include <stdio.h>
#include <stdlib.h>
/*3. Dato un insieme di valori in un array, calcolare la media dei valori e stampare in output tutti i valori minori della
media.
Stampare poi quanti sono i valori minori della media e quanti i valori maggiori.*/
#include <time.h>
#define N 10
#define MIN 1
#define MAX 100

int main()
{
	int array[N] = {};
	int i, somma=0, countMinori = 0, countMaggiori = 0;
	float media;

	srand(time(NULL));

	for (i=0; i<N; i++)
	{
		array[i] = MIN + rand() % (MAX - MIN + 1);
		printf("%d ", array[i]);
		somma += array[i];
	}
	printf("\n");

	media = (float)somma / N;
	printf("media %.2f, somma %d\n", media, somma);

	printf("Minori della media:\n");
	for (i=0; i<N; i++)
	{
		if (array[i] < media)
		{
			printf("%d ", array[i]);
			countMinori++;
		}
		else if (array[i] > media)
		{
			countMaggiori++;
		}
	}
	printf("\n");

	return 0;
}

