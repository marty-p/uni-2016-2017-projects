#include <stdio.h>
#include <stdlib.h>
/*8. Scrivere una funzione digit(n, k) che restituisca la k-esima cifra (da destra) di n. se k è maggiore del numero di cifre di n, la
funzione deve restituire 0.
• Es: digit(829, 1): 9; digit(829, 2): 2; digit(829, 3): 8.*/
int digit(int n, int k);
int main()
{
    int nInput, kInput;
    printf("Inserisci un numero:\n");
    scanf("%d", &nInput);
    printf("Inserisci la posizione della cifra da printare (da destra):\n");
    scanf("%d", &kInput);
    printf("Cifra alla n posizione (da destra): %d\n", digit(nInput, kInput));
    return 0;
}
int digit(int n, int k)
{
    int cifretotali = 1;
    n=abs(n);
    while (cifretotali < k)
    {
        n /= 10;
        cifretotali++;
    }
    return n % 10;
}
