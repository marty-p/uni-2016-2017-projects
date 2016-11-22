#include <stdio.h>
#include <stdlib.h>
/*5. Scrivere una funzione che esegua l'acquisizione di un numero e il controllo che il numero si trovi all'interno di un
determinato intervallo (min, max), mediante l'acquisizione ripetuta del numero. La funzione deve restituire sempre un valore
compreso tra min e max.*/
#include <time.h>
int randrange(int min, int max);
int main()
{
    int cdInputMin;
    int cdInputMax;
    srand(time(NULL));
    do
    {
        printf("Inserisci un numero minimo:\n");
        scanf("%d", &cdInputMin);
    }
    while (cdInputMin <= 0);
    do
    {
        printf("Inserisci un numero massimo maggiore di %d:\n", cdInputMin);
        scanf("%d", &cdInputMax);
    }
    while (cdInputMax <= cdInputMin);
    printf("%d\n", randrange(cdInputMin, cdInputMax));
    return 0;
}
int randrange(int min, int max)
{
    return min + rand() % (max-min+1);
}
