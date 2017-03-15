#include <stdio.h>
long double factorial(long double n);
int coefficienteBinomialeIterativo(int n, int k);
int coefficienteBinomialeRicorsivo(int n, int k);

int main(void)
{
	int n = 1754, k = 2;
	printf("%d == %d\n", coefficienteBinomialeIterativo(n, k), coefficienteBinomialeRicorsivo(n, k));
	return 0;
}

long double factorial(long double n)
{
	int i;
	long double res = 1;
	for (i=1; i<=n; i++)
		res *= i;
	return res;
}

int coefficienteBinomialeIterativo(int n, int k)
{
	return factorial(n)/(factorial(k)*factorial(n-k));
}

int coefficienteBinomialeRicorsivo(int n, int k)
{
	if ((k==0) || (n==k))
		return 1;
	return coefficienteBinomialeRicorsivo(n-1, k)+coefficienteBinomialeRicorsivo(n-1, k-1);
}

