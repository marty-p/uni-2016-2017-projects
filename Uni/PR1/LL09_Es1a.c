#include <stdio.h>
#include <stdlib.h>
/*1. Scrivere un programma che acquisisca tre numeri e calcoli la loro media effettuandola sulle diverse coppie, utilizzando una
funzione average(x,y).*/
#define N 3
int average(int x, int y)
{
    return (x + y) / 2;
}
int main()
{
    int numeriInput[N] = {};
    int i;
    for (i=0; i<N; i++)
    {
        printf("Inserisci il %do numero su %d:\n", i+1, N);
        scanf("%d", &numeriInput[i]);
    }
    for (i=1; i<N; i++)
    {
        printf("Media fra [%d](%d) e [%d](%d): %d\n",
               i-1, numeriInput[i-1],
               i, numeriInput[i],
               average(numeriInput[i-1], numeriInput[i])
        );
    }
    return 0;
}
