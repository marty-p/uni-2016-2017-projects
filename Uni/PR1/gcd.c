#include <stdio.h>
#include <stdlib.h>
int gcd(int u, int v)
{
	if (v==0)
		return u;
	return gcd(v, u % v);
}

int mcd(int u, int v)
{
	if (v<=0)
		return u;
	else if (u > v)
		return gcd(v, u % v);
	else if (v > u && u > 0)
		return gcd(u, v % u);
	return v;
}

int main(void)
{
	int u, v;
	printf("Enter a number 1: ");
	scanf("%d", &u);
	printf("Enter a number 2: ");
	scanf("%d", &v);
	printf("%d\n", gcd(u, v));
}

