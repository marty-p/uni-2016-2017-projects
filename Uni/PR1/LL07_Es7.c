#include <stdio.h>
#include <stdlib.h>
/*7. Scrivere un programma che prenda in ingresso una stringa e conta quante lettere doppie ci sono.*/
#include <string.h>
#include <stdbool.h> // secondo modo

#define N 30
int main()
{
	char stringa[N] = {};
	int i, conteggio;
	int l, flag_match; // primo modo
	_Bool ripetizioni[256] = {}; // secondo modo

	printf("Immetti una stringa:\n");
	scanf("%29[^\n]s", stringa);
	while ('\n'!=getchar());

	// primo modo
	conteggio = 0;
	for (i=0; i < strlen(stringa); i++)
	{
		flag_match = 0;
		for (l=0; l < i && flag_match==0; l++)
		{
			if (stringa[i] == stringa[l])
				flag_match = 1;
		}
		if (flag_match == 1)
		{
			printf("%c e' ripetuto\n", stringa[i]);
			conteggio++;
		}
	}
	printf("Ci sono %d lettere doppie\n", conteggio);

	// secondo modo
	conteggio = 0;
	for (i=0; i < strlen(stringa); i++)
	{
		if (ripetizioni[stringa[i]] == true)
		{
			printf("%c e' ripetuto\n", stringa[i]);
			conteggio++;
		}
		ripetizioni[stringa[i]] = true;
	}
	printf("Ci sono %d lettere doppie\n", conteggio);

	return 0;
}

