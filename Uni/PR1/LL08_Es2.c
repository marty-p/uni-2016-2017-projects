#include <stdio.h>
#include <stdlib.h>
/*2. Chiedere all'utente di inserire 3 frasi, e salvarle in un array di stringhe. Chiedere poi all'utente quale delle 3 frasi stampare,
quindi stampare la frase desiderata.*/
#define DIM1I 3
#define DIM2S 20
int main()
{
	char strings[DIM1I][DIM2S+1] = {};
	int i, nInput;
	for (i=0; i<DIM1I; i++)
	{
		printf("Immetti %da stringa:\n", i+1);
		scanf("%20s", strings[i]);
		getchar();
	}
	do {
		printf("Che stringa delle %d vuoi stampare? (0-%d)\n", DIM1I, DIM1I-1);
		scanf("%d", &nInput);
	} while (nInput < 0 || nInput >= DIM1I);
	printf("%s\n", strings[nInput]);
	return 0;
}

