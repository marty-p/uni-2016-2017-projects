#include <stdio.h>
#include <stdlib.h>
/*2. Scrivere un programma che acquisisca una stringa e conti il numero di caratteri spazio inseriti dall'utente.
Scriverlo inizialmente utilizzando la strlen (utilizzando un FOR), e successivamente con un ciclo che si ferma
quando incontra il carattere di escape ‘\0' (utilizzando un WHILE).*/
#include <string.h>
#define N 300

int main()
{
	int i, contatore;
	char stringa[N] = {};

	printf("immetti stringa:\n");
	scanf("%299[^\n]s", stringa);
	while ('\n'!=getchar());

	contatore=0;
	for (i=0; i<strlen(stringa); i++)
	{
		if (stringa[i]==' ')
			contatore++;
	}
	printf("spazi contati %d\n", contatore);

	i=0;
	contatore=0;
	while (stringa[i]!='\0')
	{
		if (stringa[i]==' ')
			contatore++;
		i++;
	}
	printf("spazi contati %d\n", contatore);

	return 0;
}

