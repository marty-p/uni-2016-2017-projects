#include <stdio.h>
#include <stdlib.h>
/*6. Scrivere una funzione che concatena tutte le stringhe presenti nell'array dell'esercizio precedente.
La stringa risultante deve essere allocata dinamicamente, e la sua lunghezza deve essere esattamente
pari al numero di caratteri che contiene (più il carattere \0). La funzione deve restituire poi il puntatore
al primo carattere della stringa. */
#define DIM_S 30
#define N 3
#include <string.h>
char * concatArrayOfStrings(char (*arrayStringhe)[DIM_S+1], int n);
int main()
{
	char arrayStringhe[N][DIM_S+1] = {"kek1", "kek2", "kek3"};
	char * s = NULL;
	s = concatArrayOfStrings(arrayStringhe, N);
    printf("%s\n", s);
    free(s);
    return 0;
}

char * concatArrayOfStrings(char (*arrayStringhe)[DIM_S+1], int n)
{
	int i;
	char * s = NULL;
	unsigned long last_size;

	s = calloc(1, sizeof(char));
	s[0] = '\0';

	for (i=0; i<n; i++)
	{
		// printf("1 %s -> %s\n", arrayStringhe[i], s);
		last_size = strlen(s);
		// printf("a %lu %lu\n", last_size, strlen(arrayStringhe[i]));
		s = realloc(s, last_size + strlen(arrayStringhe[i]) + sizeof('\0'));
		s[last_size] = '\0';
		// printf("2 %s -> %s\n", arrayStringhe[i], s);
		strcat(s, arrayStringhe[i]);
		// printf("3 %s -> %s\n", arrayStringhe[i], s);
		// printf("b %lu\n", strlen(s));
	}
	return s;
}

