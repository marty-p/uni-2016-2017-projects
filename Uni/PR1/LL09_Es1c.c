#include <stdio.h>
#include <stdlib.h>
/*1. Scrivere un programma che acquisisca tre numeri e calcoli la loro media effettuandola sulle diverse coppie, utilizzando una
funzione average(x,y).*/
#define N 3
float average(float x, float y);
int main()
{
    float a, b, c;
    printf("Inserisci a:\n");
    scanf("%f", &a);
    printf("Inserisci b:\n");
    scanf("%f", &b);
    printf("Inserisci c:\n");
    scanf("%f", &c);
    printf("Media fra a e b: %.2f\n", average(a, b));
    printf("Media fra b e c: %.2f\n", average(b, c));
    printf("Media fra c e a: %.2f\n", average(c, a));
    return 0;
}
float average(float x, float y)
{
    return (x + y) / 2.;
}

