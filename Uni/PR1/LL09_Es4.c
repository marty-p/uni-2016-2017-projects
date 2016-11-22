#include <stdio.h>
#include <stdlib.h>
/*4. Scrivere la funzione randrange(min, max) che rende un numero casuale compreso tra min e max (inclusi).*/
#include <time.h>
int randrange(int min, int max);
int main()
{
    int cdInputMin;
    int cdInputMax;
    srand(time(NULL));
    do {
        printf("Inserisci un numero minimo:\n");
        scanf("%d", &cdInputMin);
    } while (cdInputMin <= 0);
    do {
        printf("Inserisci un numero massimo maggiore di %d:\n", cdInputMin);
        scanf("%d", &cdInputMax);
    } while (cdInputMax <= cdInputMin);
    printf("%d\n", randrange(cdInputMin, cdInputMax));
    return 0;
}
int randrange(int min, int max)
{
    return min + rand() % (max-min+1);
}
