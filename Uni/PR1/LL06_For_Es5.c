#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* • 5. Scrivere un programma che simula un gioco tra due utenti: viene chiesto prima quanti tiri
effettuare (n), dopodiché ogni utente tira n volte un dado. Vince chi ottiene la somma dei numeri
ottenuti maggiore. */

#define N_GIOCATORI 2
#define MIN 1
#define MAX 6
int main()
{
	int i, risultato_dado_utente_uno, risultato_dado_utente_due, totale_tiro_dei_dadi;
	srand(time(NULL));

	printf("Inserire il num dei tiri dei dadi:\n");
	scanf("%d", &totale_tiro_dei_dadi);

	do {
		for (i = 0; i < totale_tiro_dei_dadi; i++)
		{
			risultato_dado_utente_uno += MIN + rand() % (MAX - MIN + 1);
			risultato_dado_utente_due += MIN + rand() % (MAX - MIN + 1);
		}
	} while (risultato_dado_utente_uno == risultato_dado_utente_due);

	printf("Risultato dei tiri: utente1 %d, utente2 %d\n", risultato_dado_utente_uno, risultato_dado_utente_due);
	if (risultato_dado_utente_uno > risultato_dado_utente_due)
		printf("Utente 1 vince\n");
	else if (risultato_dado_utente_uno < risultato_dado_utente_due)
		printf("Utente 2 vince\n");
	else
		printf("Pareggio\n"); // ambiguo

	return 0;
}

