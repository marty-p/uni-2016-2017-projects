#include <stdio.h>
#include <stdlib.h>
/*5. Dichiarare ed inizializzare a piacimento un array A, quindi normalizzarlo.
hint: normalizzare un intervallo vuol dire portare tutti gli elementi dell’intervallo ad avere valori compresi tra 0 e 1
secondo la formula x_norm = (x - min)/(max - min).*/
#include <time.h>
#define N 5
#define MIN 1
#define MAX 100

int main()
{
	float array[N] = {}; //{54, 64, 63, 74, 35}
	int i;
	float min, max;

	srand(time(NULL));

	for (i=0; i < N; i++)
	{
		array[i] = MIN + rand() % (MAX - MIN + 1);
		printf("%.2f ", array[i]);
	}
	printf("\n");

	min = max = array[0];
	for (i=1; i < N; i++)
	{
		if (array[i] < min)
			min = array[i];
		if (array[i] > max)
			max = array[i];
	}
    printf("min %.2f, max %.2f\n", min, max);

	printf("Array normalizzato:\n");
	for (i=0; i < N; i++)
	{
		array[i] = (array[i] - min)/(max - min);
		printf("%.2f ", array[i]);
	}
	printf("\n");


	return 0;
}

