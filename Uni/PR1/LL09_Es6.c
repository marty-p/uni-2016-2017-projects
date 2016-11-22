#include <stdio.h>
#include <stdlib.h>
/*6. Scrivere una funzione day_of_year(month, day, year) che restituisca il giorno dell'anno (uno compreso tra 1 e 366)
specificato dai tre argomenti.*/
#define GENNAIO 1
#define FEBBRAIO 2
#define MARZO 3
#define APRILE 4
#define MAGGIO 5
#define GIUGNO 6
#define LUGLIO 7
#define AGOSTO 8
#define SETTEMBRE 9
#define OTTOBRE 10
#define NOVEMBRE 11
#define DICEMBRE 12
int days_of_the_month(int month, int year);
int day_of_year(int month, int day, int year);
int main()
{
    int inputYear, inputMonth, inputDay;

    printf("Inserisci un anno:\n");
    scanf("%d", &inputYear);

    do {
        printf("Inserisci un mese tra 1 e 12:\n");
        scanf("%d", &inputMonth);
    } while (inputMonth < GENNAIO || inputMonth > DICEMBRE);

    do {
        printf("Inserisci un giorno tra 1 e n del mese %d:\n", inputMonth);
        scanf("%d", &inputDay);
    } while (inputDay < 1 || inputDay > days_of_the_month(inputMonth, inputYear));

    printf("giorni totali: %d\n", day_of_year(inputMonth, inputDay, inputYear));
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
            if ((year % 4)==0 && (year % 100)!=0)
                day=29;
            else
                day=28;
    }
    return day;
}
int day_of_year(int month, int day, int year)
{
    int totalDays = 0;
    int i;
    for (i=1; i < month; i++)
    {
        totalDays+=days_of_the_month(i, year);
    }
    totalDays+=day;
    return totalDays;
}
