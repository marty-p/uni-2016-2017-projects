#include <stdio.h>
#include <stdlib.h>
/*12. Scrivere una funzione nearest(n, a, b) che restituisca:
• - -1 se a è più vicino a n rispetto a b;
• - 1 se b è più vicino a n rispetto a a;
• - 0 se a e b sono equidistanti da n;
• Utilizzando questa funzione scrivere un programma che simula un gioco tra due utenti: vince chi indovina per primo il numero
n generato casualmente.*/
#include <math.h>
int nearest(int n, int a, int b);
int main()
{
    int numeromisterioso = 666;
    int input1, input2;
    int res;
    do
    {
        printf("User1: Immetti un numero:\n");
        scanf("%d", &input1);
        printf("User2: Immetti un numero:\n");
        scanf("%d", &input2);
        res = nearest(numeromisterioso, input1, input2);
    }
    while(res==0);
    if (res < 0)
        printf("Vince User1!\n");
    else
        printf("Vince User2!\n");
    return 0;
}
int nearest(int n, int a, int b)
{
    int dist_a = abs(a-n);
    int dist_b = abs(b-n);
    if (dist_a < dist_b)
        return -1;
    else if (dist_a > dist_b)
        return 1;
    return 0;
}
