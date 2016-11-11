#include <stdio.h>
#include <stdlib.h>
/*3. Scrivere un programma che stampi i primi n numeri primi. 
*/

int main()
{
	int i, k, totale_num_primi, count_numeri_primi, flag_non_primo;
    printf("Inserire il numero di numeri primi da stampare:\n");
    scanf("%d", &totale_num_primi);

	k = 1;
	count_numeri_primi = 0;
	flag_non_primo = 0;
	while (count_numeri_primi < totale_num_primi)
	{
		flag_non_primo = 0;
		for (i=2; i < k && flag_non_primo==0; i++)
		{
			if ((k % i) == 0)
			{
				flag_non_primo = 1;
			}
		}
		if (flag_non_primo==0)
		{
			printf("%d ", k);
			count_numeri_primi++;
		}
		k++;
	}
	printf("\n");

	return 0;
}

