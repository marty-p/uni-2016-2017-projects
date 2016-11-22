#include <stdio.h>
#include <stdlib.h>
/*14. Scrivere una funzione prime(i) che restituisca true se i è primo, false altrimenti. Scrivere poi un altra funzione
prime_numbers(n) che stampi i primi n numeri primi, richiamando prime(i).*/
#include <stdbool.h>
_Bool prime(int i);
void prime_numbers(int n);
int main()
{
    int n = 10;
    prime_numbers(n);
    return 0;
}
_Bool prime(int i)
{
    int j;
    _Bool flag = true;
    for (j=2; j<i && flag==true; j++)
        if ((i%j) == 0)
            flag = false;
    return flag;
}
void prime_numbers(int n)
{
    int counter = 0;
    int i=1;
    while (counter < n)
    {
        if (prime(i)==true)
        {
            printf("%d ", i);
            counter++;
        }
        i++;
    }
    printf("\n");
}
