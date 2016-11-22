#include <stdio.h>
#include <stdlib.h>
/*7. Scrivere una funzione che restituisca il numero di cifre presenti in un numero passato come parametro.*/
#include <math.h>
int contacifre(int n);
int main()
{
    int cdInput;
    printf("Inserisci un numero:\n");
    scanf("%d", &cdInput);
    printf("Cifre presenti: %d\n", contacifre(cdInput));
    return 0;
}
int contacifre(int n)
{
    int cifretotali = 1;
    n=abs(n);
    while (n > 9)
    {
        n /= 10;
        cifretotali++;
    }
    return cifretotali;
}
