#include <stdio.h>
#include <stdlib.h>
/*14. Scrivere una funzione di inner product tra due vettori di dimensione n, che restituisca il valore a[0]*b[0]
+ a[1]*b[1] + ... + a[n-1]*b[n-1].*/
#define DIM 4
int inner_product(int a[], int b[], int n);

int main()
{
    int array1[DIM] = {1, 2, 3, 4};
    int array2[DIM] = {5, 6, 7, 8};
	printf("inner_product di array1 e array2 = %d\n", inner_product(array1, array2, DIM));
	return 0;
};

int inner_product(int a[], int b[], int n)
{
	int i;
	int res=0;
	for (i=0; i<n; i++)
		res+=a[i]*b[i];
	return res;
}

