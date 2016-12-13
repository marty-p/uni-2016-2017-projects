#include <stdio.h>
#include <stdlib.h>
/*1. Scrivere una funzione che, ricevuto come parametro un numero di gradi Celsius, lo trasformi in
Fahrenheit secondo la formula F=(C*1.8) + 32. Utilizzare solamente variabili allocate dinamicamente. */
void c2f(float C, float * F);
int main()
{
	float * pCelsius = NULL;
	float * pFahrenheit = NULL;
	pCelsius = malloc(sizeof(float));
	if (pCelsius == NULL)
		return -1;
	pFahrenheit = malloc(sizeof(float));
	if (pFahrenheit == NULL)
		return -1;
	*pCelsius = 30.0;
	c2f(*pCelsius, pFahrenheit);
    printf("%.2f to %.2f\n", *pCelsius, *pFahrenheit);
    free(pCelsius);
    free(pFahrenheit);
    return 0;
}

void c2f(float C, float * F)
{
	*F = (C*1.8) + 32;
}

