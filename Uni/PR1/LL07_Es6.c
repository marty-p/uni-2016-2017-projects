#include <stdio.h>
#include <stdlib.h>
/*6. Scrivere un programma che prenda in ingresso una stringa e stampa in output se la stringa è palindroma. Una
stringa è palindroma se può essere letta nello stesso modo da sinistra verso destra e da destra verso sinistra.
*/
#include <string.h>
#define N 30

int main()
{
	int i, l;
	int notmatch_flag = 0;
	char s1[N] = {};

	printf("scrivi una stringa:\n");
	scanf("%29[^\n]s", s1);
	while ('\n'!=getchar());

	for (i=0, l=strlen(s1)-1; i < strlen(s1)/2 && notmatch_flag==0; i++, l--)
	{
		printf("%c != %c\n", s1[i], s1[l]);
		if (s1[i] != s1[l])
			notmatch_flag = 1;
	}
	if (notmatch_flag)
		printf("%s non e' palindroma\n", s1);
	else
		printf("%s e' palindroma\n", s1);
	return 0;
}

