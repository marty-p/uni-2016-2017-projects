#include <stdio.h>
#include <stdlib.h>
/*2. Scrivere una funzione ricorsiva che stampi gli elementi di un array. */
#define N 5
void rec_print_array(int array[], int n);

int main()
{
    int array[N] = {11, 22, 33, 44, 55};
    rec_print_array(array, N);
    return 0;
}

void rec_print_array(int array[], int n)
{
    if (n==0)
    {
        printf("\n");
        return;
    }
    else
        printf("%d ", *array);
    rec_print_array(array+1, n-1);
}

