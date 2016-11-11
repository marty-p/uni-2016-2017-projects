#include <stdio.h>
#include <stdlib.h>
/*4. Scrivere un filtro B1FF, che legga una stringa inserita dall'utente e la modifica secondo le seguenti regole:
- tutte le lettere diventano maiuscole;
- le seguenti lettere vengono trasformate nei seguenti numeri: A->4, B->8, E->3, I->1, O->0, S->5;
- il messaggio finisce sempre con la sequenza: "..!!1!1".*/
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
		switch (stringa[i])
		{
			case 'A':
				stringa[i]='4';
				break;
			case 'B':
				stringa[i]='8';
				break;
			case 'E':
				stringa[i]='3';
				break;
			case 'I':
				stringa[i]='1';
				break;
			case 'O':
				stringa[i]='0';
				break;
			case 'S':
				stringa[i]='5';
				break;
		}
	}
	strcat(stringa, "..!!1!1");
	printf("%s\n", stringa);
	return 0;
}

