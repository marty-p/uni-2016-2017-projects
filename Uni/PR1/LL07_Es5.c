#include <stdio.h>
#include <stdlib.h>
/*5. Scrivere un programma che prenda in ingresso due stringhe, s1 ed s2, e stampa se la stringa s2 è
completamente contenuta in s1 o meno. Per ”completamente contenuta” si intende che i caratteri di s2 devono
essere presenti in s1 nella stessa sequenza in cui compaiono in s2. Ad esempio, la stringa ”zio” è contenuta in
”funzione”.*/
#include <string.h>

int main()
{
	int match_flag = 0;
	int i, l;
	char s1[30] = {};
	char s2[30] = {};

	printf("prima stringa:\n");
	scanf("%29[^\n]s", s1);
	while ('\n'!=getchar());

	printf("seconda stringa:\n");
	scanf("%29[^\n]s", s2);
	while ('\n'!=getchar());

	printf("s1: %s, s2:%s\n", s1, s2);

	for (i=0, l=0; i<=strlen(s1) && match_flag==0; i++)
	{
		if (s1[i] == s2[l])
		{
			printf("l %d strlen %lu char %c\n", l, strlen(s2), s2[l]);
			l++;
			if (l >= strlen(s2))
				match_flag = 1;
		}
		else if (l > 0)
			l = 0;
	}

	if (match_flag)
		printf("%s sta interamente su %s\n", s2, s1);
	else
		printf("%s non sta su %s\n", s2, s1);
	return 0;
}

