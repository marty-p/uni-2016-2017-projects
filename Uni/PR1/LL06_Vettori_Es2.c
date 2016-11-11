#include <stdio.h>
#include <stdlib.h>
/*2. Dato in input un numero intero, dire se il numero possiede delle cifre ripetute. Comunicare quali sono le cifre
ripetute.
hint: usare un array di valori booleani, dove ogni posizione è legata ad una cifra.
*/
#include <stdbool.h>
#define N 10

int main()
{
	_Bool array[N] = {0};
	int numero, cifra;

	printf("Immetti un numero:\n");
	scanf("%d", &numero);
	while (numero > 0)
	{
		cifra = numero % 10;
		if (array[cifra] == true)
			printf("%d e' ripetuto\n", cifra);
		array[cifra] = true;
		numero /= 10;
	}

	return 0;
}

