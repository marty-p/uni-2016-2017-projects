#include <stdio.h>
#include <stdlib.h>
/*6. Dichiarare un vettore A ed inizializzarlo in maniera casuale. Trovare l’elemento tra quelli presenti più vicino ad un
numero inserito dall'utente
*/
#include <time.h>
#include <math.h>
#define N 10
#define MIN 1
#define MAX 100

int main()
{
	int array[N];
	int i, k, numero_scelto;
	int numero_vicino, differenza_n_vicino;
	srand(time(NULL));

	for (i=0; i < N; i++)
	{
		array[i] = MIN + rand() % (MAX - MIN + 1);
		printf("%d ", array[i]);
	}
	printf("\n");

	printf("Inserisci un numero:\n");
	scanf("%d", &numero_scelto);

	numero_vicino = array[0];
	differenza_n_vicino = abs(array[0]);
	for (i=1; i < N; i++)
	{
		k = abs(array[i] - numero_scelto);
		printf("[%d] %d - %d = %d abs\n", i, array[i], numero_scelto, k);
		// salta maggiori o uguali
		if (k < differenza_n_vicino)
		{
			numero_vicino = array[i];
			differenza_n_vicino = k;
		}
	}
	printf("Numero piu' vicino: %d (distanza %d)\n", numero_vicino, differenza_n_vicino);

	return 0;
}

