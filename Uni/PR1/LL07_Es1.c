#include <stdio.h>
#include <stdlib.h>
/*1. Scrivere un programma che acquisisca una stringa e la modifichi trasformando tutti i caratteri minuscoli in
maiuscoli e viceversa (lasciando inalterati tutti gli altri caratteri).*/
#include <string.h>
#define N 30

int main()
{
	int i;
	char stringa[N] = {};

	printf("immetti stringa:\n");
	scanf("%29[^\n]s", stringa);
	while ('\n'!=getchar());

	for (i=0; i<strlen(stringa); i++)
	{
		if ('a' <= stringa[i] && stringa[i] <= 'z')
			stringa[i] += 'A' - 'a';
		else if ('A' <= stringa[i] && stringa[i] <= 'Z')
			stringa[i] += 'a' - 'A';
	}
	printf("%s\n", stringa);
	return 0;
}

