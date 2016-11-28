#include <stdio.h>
#include <stdlib.h>
/*7. Dichiarare un'enumerazione rappresentante i giorni della settimana. Includere tale tipo
nella struttura data dell'esercizio 2. Scrivere una funzione che dato in input il giorno di un
mese e il relativo giorno di una settimana e un altro giorno dello stesso mese, restituisca il
relativo giorno della settimana di quest'ultimo.*/
#define N_WEEK 7
typedef enum eSettimana_s { LUNEDI, MARTEDI, MERCOLEDI, GIOVEDI, VENERDI, SABATO, DOMENICA } eSettimana;

typedef struct date_s {
	int giorno;
	int mese;
	int anno;
	eSettimana settimana;
} date;

eSettimana spot_the_week_day(int giornoEsempio, eSettimana settimanaEsempio, int giornoDaScoprire);

int main()
{
	char weeks[N_WEEK][10] = {"lunedi", "martedi", "mercoledi", "giovedi", "venerdi", "sabato", "domenica"};
	date data = {};
	int giornoDaScoprire;
	int i;

	printf("Inserisci un giorno di esempio:\n");
	scanf("%d", &data.giorno);

	do {
		printf("Inserisci il numero di settimana del giorno di esempio tra %d e %d:\n", LUNEDI, DOMENICA);
		scanf("%d", &data.settimana);
	} while (data.settimana < LUNEDI || data.settimana > DOMENICA);

	printf("Inserisci il giorno da scoprire:\n");
	scanf("%d", &giornoDaScoprire);

	// printa il giorno specificato
	printf("> %s < \n", weeks[spot_the_week_day(data.giorno, data.settimana, giornoDaScoprire)]);

	// printa l'intero mese
	for (i=1; i < 31; i++)
		printf("> giorno %d = %s < \n", i, weeks[spot_the_week_day(data.giorno, data.settimana, i)]);
	return 0;
}

eSettimana spot_the_week_day(int giornoEsempio, eSettimana settimanaEsempio, int giornoDaScoprire)
{
	eSettimana fstWeek = giornoEsempio % N_WEEK;
	eSettimana sndWeek = giornoDaScoprire % N_WEEK;
	int compl7 = N_WEEK - (fstWeek - sndWeek);
	return (settimanaEsempio + compl7) % N_WEEK;
}

