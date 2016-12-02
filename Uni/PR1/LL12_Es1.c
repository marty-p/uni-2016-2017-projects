#include <stdio.h>
#include <stdlib.h>
/*1. Scrivere una funzione ricorsiva che calcoli l'n-esimo numero di fibonacci, dove:
f(n) = f(n-1)+f(n-2)
La serie di fibonacci è la seguente: (0) 1 1 2 3 5 8 13 21 ... */
int fibonacci(int n);

int main()
{
    int nInput;
    do
    {
        printf("Immetti un numero positivo:\n");
        scanf("%d", &nInput);
    }
    while (nInput < 0);

    printf("%d", fibonacci(nInput));
    return 0;
}

int fibonacci(int n)
{
    if (n==0)
        return 0;
    else if (n==1)
        return 1;
    return fibonacci(n-1)+fibonacci(n-2);
}

