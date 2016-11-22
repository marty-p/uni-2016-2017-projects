#include <stdio.h>
#include <stdlib.h>
/*3. Scrivere la funzione randmod(n) che rende un numero casuale compreso tra 0 e n-1.*/
#include <time.h>
int randmod(int n);
int main()
{
    int cdInput;
    srand(time(NULL));
    do
    {
        printf("Inserisci un numero:\n");
        scanf("%d", &cdInput);
    }
    while (cdInput <= 0);
    printf("%d\n", randmod(cdInput));
    return 0;
}
int randmod(int n)
{
    return rand() % n;
}
