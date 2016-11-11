#include <stdio.h>
#include <stdlib.h>
/*3. Scrivere un programma che cerchi la "maggiore" e la "minore" tra una serie di parole inserite dall'utente.*/
#include <string.h>
#define N 6
#define DIM 30

int main()
{
	char stringhe[N][DIM] = {};
	int i;
	int pos_minore=0, pos_maggiore=0;

	for (i=0; i<N; i++)
	{
		printf("scrivi la %da stringa:\n", i+1);
		scanf("%29[^\n]s", stringhe[i]);
		while ('\n'!=getchar());
	}

	for (i=1; i<N; i++)
	{
		// stringa i minore di stringa minore
		if (strcmp(stringhe[pos_minore], stringhe[i]) > 0)
			pos_minore = i;
		// stringa i maggiore di stringa maggiore
		else if (strcmp(stringhe[pos_maggiore], stringhe[i]) < 0)
			pos_maggiore = i;
	}

	printf("stringa minore in pos %d: %s\n", pos_minore, stringhe[pos_minore]);
	printf("stringa maggiore in pos %d: %s\n", pos_maggiore, stringhe[pos_maggiore]);
	return 0;
}

