#include <stdio.h>
#include <stdlib.h>
/*10. Scrivere una funzione che calcoli in maniera iterativa il fattoriale di un numero preso in ingresso.*/
//long long int factorial(int n)
int factorial(int n);
int main()
{
    int nInput;
    do
    {
        printf("Inserisci un numero:\n");
        scanf("%d", &nInput);
    }
    while (nInput < 0);
    //printf("Fattoriale: %I64d\n", factorial(nInput));
    printf("Fattoriale: %d\n", factorial(nInput));
    return 0;
}
int factorial(int n)
{
    printf("n: %d\n", n);
    if (n == 0)
        return 1;
    return n*factorial(n-1);
}
