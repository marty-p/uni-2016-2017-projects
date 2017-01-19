#include <stdio.h>
#include <stdlib.h>
int f(int n)
{
	if (n == 2)
		return 1;
	else if (n >= 3)
		return f(n-1) + f(n-2) + f(n-3);
	return 0;
}
int main(void)
{
	int n;
	printf("Enter a number: ");
	scanf("%d", &n);
	printf("%d\n", f(n));
}

