#include <stdio.h>
#include <stdlib.h>
/*Far inserire due frasi all’utente e contare le occorrenze delle vocali. Comunicare poi
la dimensione delle due stringhe e il numero di vocali contenute in ognuna.*/
#include <string.h>
#define DIM1I 2
#define DIM2J 50
#define MIN 0
#define MAX 100
int main()
{
	char strings[DIM1I][DIM2J+1] = {};
	int i, j;
	int conteggio_vocali[DIM1I] = {};

	for (i=0; i<DIM1I; i++)
	{
		printf("Immetti %da stringa:\n", i+1);
		scanf("%50[^\n]s", strings[i]);
		while (getchar()!='\n') ;
	}

	for (i=0; i<DIM1I; i++)
	{
		for (j=0; j<DIM2J; j++)
		{
			switch (strings[i][j])
			{
				case 'A':
				case 'a':
				case 'E':
				case 'e':
				case 'I':
				case 'i':
				case 'O':
				case 'o':
				case 'U':
				case 'u':
					conteggio_vocali[i]++;
					break;
			}
		}
		printf("La stringa in indice %d misura %ld caratteri e ha %d vocali\n", i, strlen(strings[i]), conteggio_vocali[i]);
	}

	return 0;
}

