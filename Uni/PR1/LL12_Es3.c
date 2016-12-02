#include <stdio.h>
#include <stdlib.h>
/*3. Scrivere una funzione ricorsiva che calcoli la somma degli elementi di un array*/
#define N 5
int rec_sum_array(int array[], int n);

int main()
{
    int array[N] = {11, 22, 33, 44, 55};
    printf("%d\n", rec_sum_array(array, N));
    return 0;
}

int rec_sum_array(int array[], int n)
{
    if (n==0)
        return 0;
    return *array + rec_sum_array(array+1, n-1);
}

