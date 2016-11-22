#include <stdio.h>
#include <stdlib.h>
/*2. Scrivere un programma che acquisisca un numero e stampi un conto alla rovescia a partire dal numero acquisito.
Utilizzare una procedura che si occupa di stampare il numero.*/
void countdown(int n); //way1
void printarellomatto(int n); //way2

int main()
{
    int cdInput;
    int i; //way2
    do {
        printf("Inserisci un numero:\n");
        scanf("%d", &cdInput);
    } while (cdInput < 0);
    //way1
    countdown(cdInput);
    //way2
    for (i=cdInput; i>=0; i--)
        printarellomatto(i);
    return 0;
}
void countdown(int n) //way1
{
    int i;
    for (i=n; i>=0; i--)
        printf("%d\n", i);
}
void printarellomatto(int n) //way2
{
    printf("%d\n", n);
}
