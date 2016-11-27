#include <stdio.h>
#include <stdlib.h>
/*2. Scrivere una funzione swap(x,y) che scambi il valore delle variabili in argomento.*/
void swap(int * x, int * y);

int main()
{
    int a = 123;
	int b = 456;
	swap(&a, &b);
	printf("a = %d, b = %d\n", a, b);
    return 0;
}

void swap(int * x, int * y)
{
	int t = *x;
	*x = *y;
	*y = t;
}

