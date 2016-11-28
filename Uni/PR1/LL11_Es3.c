#include <stdio.h>
#include <stdlib.h>
/*3. Implementare una struttura time composta da ore, minuti e secondi. Scrivere una funzione
che, preso in ingresso un numero di secondi, restituisce una struttura time scomponendo il
numero di secondi in ore, minuti e secondi. */

enum eTime { SECONDI_IN_MINUTO = 60, MINUTI_PER_ORE = 60, SECONDI_PER_ORE = SECONDI_IN_MINUTO*MINUTI_PER_ORE};
typedef struct time_s {
	int ore;
	int minuti;
	int secondi;
} time;

time immetti_tempo()
{
	int inputSecondi;
	time tempo = {};

	printf("Immetti n secondi:\n");
	scanf("%d", &inputSecondi);

	tempo.ore = inputSecondi / SECONDI_PER_ORE;
	inputSecondi %= SECONDI_PER_ORE;

	tempo.minuti = inputSecondi / SECONDI_IN_MINUTO;
	inputSecondi %= SECONDI_IN_MINUTO;

	tempo.secondi = inputSecondi;
	return tempo;
}

int main()
{
	time tempo = immetti_tempo();
	printf("H%02d:M%02d:S%02d\n", tempo.ore, tempo.minuti, tempo.secondi);
	return 0;
}

