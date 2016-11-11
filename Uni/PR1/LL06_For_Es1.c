#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*1. Scrivere un programma che chieda all'utente un numero N e stampi tutti i quadrati pari compresi
tra 1 e n.
Es: inserendo 10, il programma deve stampare la successione 4, 16, 36, 64, 100
*/

int main()
{
	int i, num, quadrato;
    printf("Inserire un numero:\n");
    scanf("%d", &num);
	for (i=1; i < num; i++)
	{
		quadrato = pow(i, 2); // + 0.5
		if ((quadrato % 2) == 0)
			printf("%d ", quadrato);
	}
	return 0;
}

