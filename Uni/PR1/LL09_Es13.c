#include <stdio.h>
#include <stdlib.h>
/*13. Scrivere un programma che trovi il minimo in un array dichiarato nel main, scrivendo una funzione min(x,y) che restituisca
il valore minore tra x e y. Scrivere una versione del programma che trovi il massimo.*/
#define N 6
int min(int x, int y);
int main()
{
    int array[N] = {22, 33, 44, 11, 66, 55};
    int minore = array[0];
    int i;
    for (i=1; i<N; i++)
        minore = min(minore, array[i]);
    printf("minore: %d\n", minore);
    return 0;
}
int min(int x, int y)
{
    if (x > y)
        return y;
    return x;
}
