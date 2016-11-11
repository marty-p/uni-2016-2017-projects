#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* 4. Scrivere un programma che permetta di convertire numeri binari in decimale. Il programma
acquisisce prima il numero di cifre che formano il numero binario, dopodiché acquisisce una per
volta le cifre del numero binario. */

int main()
{
	int i, num_convertito, num_cifre_binarie, num_binario, cifra_binaria;

	printf("Inserire il num delle cifre binarie:\n");
	scanf("%d", &num_cifre_binarie);

	num_binario = 0;
	for (i=num_cifre_binarie-1; 0 <= i; i--) // da sinistra a destra
	{
		printf("Inserire la %da cifra binaria:\n", i+1);
		scanf("%d", &cifra_binaria);
		num_binario += cifra_binaria * (pow(10, i));
	}

	printf("Numero binario inserito %d\n", num_binario);

	i = 0;
	num_convertito = 0;
	while (num_binario > 0)
	{
		num_convertito += pow((num_binario % 10) *2, i);
		num_binario /= 10;
		i++;
	}
	printf("Numero binario convertito %d\n", num_convertito);

	return 0;
}

