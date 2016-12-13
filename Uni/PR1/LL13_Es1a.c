#include <stdio.h>
#include <stdlib.h>
/*1. Scrivere una funzione che, ricevuto come parametro un numero di gradi Celsius, lo trasformi in
Fahrenheit secondo la formula F=(C*1.8) + 32. Utilizzare solamente variabili allocate dinamicamente. */
int * c2f(int C);
int main()
{
	int * pCelsius = NULL;
	int * pFahrenheit = NULL;
	pCelsius = malloc(sizeof(int));
	*pCelsius = 30;
	pFahrenheit = c2f(*pCelsius);
    printf("%d to %d\n", *pCelsius, *pFahrenheit);
    free(pCelsius);
    free(pFahrenheit);
    return 0;
}
int * c2f(int C)
{
	int * F = NULL;
	F = malloc(sizeof(int));
	*F = (C*1.8) + 32;
	return F;
}

