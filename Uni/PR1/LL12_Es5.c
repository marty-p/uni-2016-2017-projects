#include <stdio.h>
#include <stdlib.h>
/*5. Scrivere una funzione ricorsiva che, avendo in input un array di n interi, dia in output true se
10 è un elemento dell'array, false altrimenti. */
#include <stdbool.h>
#define N 5
_Bool rec_is_in_array(int array[], int n, int elem);
int main()
{
    int array1[N] = {11, 22, 33, 44, 55};
    int array2[N] = {11, 22, 33, 10, 55};
    printf("array1 %d\n", rec_is_in_array(array1, N, 10));
    printf("array2 %d\n", rec_is_in_array(array2, N, 10));
    return 0;
}

_Bool rec_is_in_array(int array[], int n, int elem)
{
    if (n==0)
        return false;
    if (*array == elem)
        return true;

    return rec_is_in_array(array+1, n-1, elem);
}

