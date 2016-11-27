#include <stdio.h>
#include <stdlib.h>
/*12. Scrivere una funzione che verifichi se due intervalli (min1,max1) e (min2,max2) si sovrappongono. Se si
la funzione restituirà vero e il punto medio della loro sovrapposizione si troverà in un argomento di output,
altrimenti renderà falso.*/
#include <time.h>
#include <stdbool.h>
#define DIM 6
_Bool minmax_overlap(int min1, int max1, int min2, int max2, int * puntomedio);
int min(int a, int b);
int max(int a, int b);

int main()
{
	int min1 = 10, max1 = 100, min2 = 30, max2 = 60;
	int puntomedio = 0;
	if (minmax_overlap(min1, max1, min2, max2, &puntomedio) == true)
		printf("min1 %d, max1 %d, min2 %d, max2 %d, puntomedio %d\n", min1, max1, min2, max2, puntomedio);
	else
		printf("min1 %d, max1 %d, min2 %d, max2 %d, non sovrapposti\n", min1, max1, min2, max2);
	return 0;
}

_Bool minmax_overlap(int min1, int max1, int min2, int max2, int * puntomedio)
{
	int max_of_min = max(min1, min2);
	int min_of_max = min(max1, max2);
	if (max_of_min <= min_of_max)
	{
		*puntomedio = max_of_min + ((min_of_max-max_of_min)/2);
		// printf("%d %d\n", max_of_min, min_of_max);
		return true;
	}
	return false;
}

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

