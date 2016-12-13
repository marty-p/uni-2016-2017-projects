#include <stdio.h>
#include <stdlib.h>
/*6. Scrivere una funzione che concatena tutte le stringhe presenti nell'array dell'esercizio precedente.
La stringa risultante deve essere allocata dinamicamente, e la sua lunghezza deve essere esattamente
pari al numero di caratteri che contiene (più il carattere \0). La funzione deve restituire poi il puntatore
al primo carattere della stringa. */
#define DIM_S 30
#define N 3
#include <string.h>
// char * concatArrayOfStrings(int n, char * arrayStringhe[n]);
char * concatArrayOfStrings(int n, char ** arrayStringhe);
int main()
{
	char **arrayStringhe = NULL;
	char * s = NULL;
	int i;

	arrayStringhe = calloc(N, sizeof(char *));
	if (NULL == arrayStringhe)
		return -1;

	for (i=0; i<N; i++)
	{
		arrayStringhe[i] = calloc(DIM_S+1, sizeof(char));
		if (NULL == arrayStringhe[i])
			return -1;
		snprintf(arrayStringhe[i], DIM_S+1, "kek%d", i+1);
	}

	s = concatArrayOfStrings(N, arrayStringhe);
    printf("%s\n", s);

	for (i=0; i<N; i++)
		free(arrayStringhe[i]);
	free(arrayStringhe);
    free(s);
    return 0;
}

// char * concatArrayOfStrings(int n, char * arrayStringhe[n])
char * concatArrayOfStrings(int n, char ** arrayStringhe)
{
	int i;
	char * s = NULL;
	unsigned long last_size;

	s = calloc(1, sizeof(char));
	s[0] = '\0';

	for (i=0; i<n; i++)
	{
		last_size = strlen(s);
		s = realloc(s, last_size + strlen(arrayStringhe[i]) + sizeof('\0'));
		s[last_size] = '\0';
		strcat(s, arrayStringhe[i]);
	}
	return s;
}

