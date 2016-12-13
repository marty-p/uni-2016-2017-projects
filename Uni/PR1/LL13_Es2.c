#include <stdio.h>
#include <stdlib.h>
/*2. Scrivere una funzione "duplicate" che utilizzi l'allocazione dinamica per creare una copia di una
stringa.*/
#include <string.h>
char* duplicate(char* s);
int main()
{
	char * s = NULL;
	s = duplicate("Hello world!");
    printf("%s\n", s);
    free(s);
    return 0;
}

char* duplicate(char* stringa)
{
	char * s = NULL;
	s = calloc(strlen(stringa)+1, sizeof(char));
	strcpy(s, stringa);
	return s;
}

