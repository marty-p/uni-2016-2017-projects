#include <stdio.h>
#include <stdlib.h>
/*1. Scrivere un programma che acquisisca tre numeri e calcoli la loro media effettuandola sulle diverse coppie, utilizzando una
funzione average(x,y).*/
#define N 3
float average(float x, float y)
{
    return (x + y) / 2.;
}
int main()
{
    float numeriInput[N] = {};
    int i;
    for (i=0; i<N; i++)
    {
        printf("Inserisci il %do numero su %d:\n", i+1, N);
        scanf("%f", &numeriInput[i]);
    }
    for (i=1; i<N; i++)
    {
        printf("Media fra [%d](%.2f) e [%d](%.2f): %.2f\n",
               i-1, numeriInput[i-1],
               i, numeriInput[i],
               average(numeriInput[i-1], numeriInput[i])
        );
    }
    return 0;
}
