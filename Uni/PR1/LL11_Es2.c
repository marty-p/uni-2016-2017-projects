#include <stdio.h>
#include <stdlib.h>
/*2. Implementare una struttura ‘date’ composta da giorno, mese e anno. Acquisire una data
inserita dall'utente e scrivere una funzione che verifichi se la data inserita è una data valida. */
#include <stdbool.h>

enum eMesi { GENNAIO=1, FEBBRAIO, MARZO, APRILE, MAGGIO, GIUGNO, LUGLIO, AGOSTO, SETTEMBRE, OTTOBRE, NOVEMBRE, DICEMBRE };

typedef struct date_s {
	int giorno;
	int mese;
	int anno;
} date;

int days_of_the_month(int month, int year);
_Bool check_date(date * data);

int main()
{
	date data = {};

	printf("Inserisci giorno:\n");
	scanf("%d", &data.giorno);
	printf("Inserisci mese:\n");
	scanf("%d", &data.mese);
	printf("Inserisci anno:\n");
	scanf("%d", &data.anno);

	if (check_date(&data))
		printf("La data e' corretta\n");
	else
		printf("La data e' sbagliata\n");
	return 0;
}

int days_of_the_month(int month, int year)
{
    int day=0;
    switch (month)
    {
        case GENNAIO:
        case MARZO:
        case MAGGIO:
        case LUGLIO:
        case AGOSTO:
        case OTTOBRE:
        case DICEMBRE:
            day=31;
            break;
        case APRILE:
        case GIUGNO:
        case SETTEMBRE:
        case NOVEMBRE:
            day=30;
            break;
        case FEBBRAIO:
            if ((year % 4)==0 && ((year % 100)!=0 || (year % 400)==0))
                day=29;
            else
                day=28;
    }
    return day;
}

_Bool check_date(date * data)
{
	if (data == NULL)
		return false;

	if (data->mese < GENNAIO || data->mese > DICEMBRE)
		return false;

	if (data->giorno < 1 || data->giorno > days_of_the_month(data->mese, data->anno))
		return false;

	return true;
}

