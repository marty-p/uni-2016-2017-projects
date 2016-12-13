#include <stdio.h>
#include <stdlib.h>
/*5. Scrivere un programma che permetta di visualizzare la k-esima stringa tra le n inserite dall'utente in
un array di stringhe. Chiedere inizialmente all'utente quante stringhe vuole inserire, dopodiché
acquisirle una alla volta. L'array deve essere allocato dinamicamente.*/
#define DIM_S 30
int main()
{
	char ** arrayStringhe = NULL;
	int inputNStringhe;
	int inputPosStringaDaStampare;
	int i;

	printf("Quante stringhe vuoi acquisire:\n");
	scanf("%d", &inputNStringhe);
	getchar();
	arrayStringhe = calloc(inputNStringhe, sizeof(char *));
	if (NULL == arrayStringhe)
		return -1;

	for (i=0; i<inputNStringhe; i++)
	{
		arrayStringhe[i] = calloc(DIM_S+1, sizeof(char));
		if (NULL == arrayStringhe[i])
			return -1;
		printf("Immetti stringa n%02d\n", i+1);
		scanf("%30[^\n]s", arrayStringhe[i]);
		getchar();
	}

	for (i=0; i<inputNStringhe; i++)
	{
		printf("%s\n", arrayStringhe[i]);
	}

	do {
		printf("Quale stringa vuoi stampare tra 0-%d?\n", inputNStringhe-1);
		scanf("%d", &inputPosStringaDaStampare);
		getchar(); // clean non-number characters if inputted, otherwise infinite loop
	} while (inputPosStringaDaStampare < 0 || inputPosStringaDaStampare >= inputNStringhe);
	printf("%s\n", arrayStringhe[inputPosStringaDaStampare]);

	for (i=0; i<inputNStringhe; i++)
		free(arrayStringhe[i]);
	free(arrayStringhe);
    return 0;
}

