#include <stdio.h>
#include <stdlib.h>
/*1. Scrivere una funzione int decompose(float f, float * d) che, dato il numero f, salvi in d la
parte decimale di f e restituisca la parte intera.*/
int decompose(float f, float * d);

int main()
{
    float f = 666.0f;
	float g = 0.0f;
	int ret = decompose(f, &g);
	printf("f = %.2f, g = %.2f, ret = %d\n", f, g, ret);
    return 0;
}

int decompose(float f, float * d)
{
	int parte_intera = f;
	*d = f - parte_intera;
	return parte_intera;
}

