#include <stdio.h>
#include <stdlib.h>
/*9. Sia P una matrice NxN che rappresenta il tabellone di un campionato. P deve essere inizializzata in modo casuale, e
l’elemento [i][j] può avere un valore che indica il pareggio, la vittoria della squadra di casa (i) e un valore che indica la vittoria
della squadra in trasferta. Definire quindi un vettore C di dimensione N che contenga, per ciascuna squadra il punteggio
totalizzato (3 punti per la vittoria, 1 per il pareggio, 0 per le sconfitte). Indicare quale delle N squadre ha vinto il campionato.*/
#include <time.h>
#define N 10
#define MIN 0
#define MAX 2
#define VITTORIA 2
#define PAREGGIO 1
#define SCONFITTA 0
#define PUNTI_VITTORIA 3
#define PUNTI_PAREGGIO 1
#define PUNTI_SCONFITTA 0
int main()
{
	int P[N][N] = {};
	int C[N] = {};
	int i, j;
	srand(time(NULL));

	for (i=0; i<N; i++)
	{
		for (j=0; j<N; j++)
		{
			P[i][j] = MIN + rand() % (MAX - MIN + 1);
			printf("%3d, ", P[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (i=0; i<N; i++)
	{
		for (j=0; j<N; j++)
		{
			if (P[i][j] == VITTORIA)
				C[i] += PUNTI_VITTORIA;
			else if (P[i][j] == PAREGGIO)
				C[i] += PUNTI_PAREGGIO;
			else if (P[i][j] == SCONFITTA)
				C[i] += PUNTI_SCONFITTA;
		}
		printf("%3d, ", C[i]);
		printf("\n");
	}
	printf("\n");

	return 0;
}

