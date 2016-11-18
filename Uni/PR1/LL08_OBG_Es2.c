#include <stdio.h>
#include <stdlib.h>
/*Stampare il contenuto di una matrice di caratteri.
Prima utilizzando due for carattere per carattere e successivamente riga per riga
tenendo a mente che ogni riga di una matrice di caratteri è una stringa.
Dichiarare ed inizializzare la matrice a livello di codice.*/
#define DIM1I 3
#define DIM2J 4
#define MIN 0
#define MAX 100
int main()
{
	char matrix[DIM1I][DIM2J] = {
		{'k','a','k','\0'},
		{'k','e','k','\0'},
		{'k','i','k','\0'},
	};
	int i, j;

	for (i=0; i<DIM1I; i++)
	{
		for (j=0; j<DIM2J; j++)
		{
			printf("%c, ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (i=0; i<DIM1I; i++)
	{
		printf("%s, ", matrix[i]);
		printf("\n");
	}
	printf("\n");

	return 0;
}

