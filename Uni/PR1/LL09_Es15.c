#include <stdio.h>
#include <stdlib.h>
/*15. Scrivere una funzione che prenda come parametro un carattere:
• - se è una lettera minuscola, restituisce una lettera maiuscola;
• - se è una lettera maiuscola, restituisce una lettera minuscola;
• - lascia invariati tutti gli altri caratteri.
• Modificare successivamente una stringa dichiarata nel main modificando ogni carattere utilizzando la funzione appena
descritta.*/
#include <string.h>
char reversecase(char c);
int main()
{
    char stringa[] = "BigBoss666";
    int i;
    printf("prima: %s\n", stringa);
    for (i=0; i<strlen(stringa); i++)
    {
        stringa[i] = reversecase(stringa[i]);
    }
    printf("dopo: %s\n", stringa);
    return 0;
}
char reversecase(char c)
{
    if ('A' <= c && c <= 'Z')
        c += 'a'-'A';
    else if ('a' <= c && c <= 'z')
        c -= 'a'-'A';
    return c;
}
