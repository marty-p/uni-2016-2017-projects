#include <stdio.h>
#include <stdlib.h>
/*2. Scrivere un programma che stampi il calendario di un mese. L'utente deve specificare il numero di
giorni nel mese e il giorno della settimana in cui questo comincia (0: lunedi', 6: domenica). 
*/

int main()
{
	int i, num_giorni_mese, num_giorno_settimana;
    printf("Inserire il numero di giorni del mese:\n");
    scanf("%d", &num_giorni_mese);

    printf("Inserire il numero del giorno della settimana:\n");
    scanf("%d", &num_giorno_settimana);
	for (i=0; i < num_giorni_mese; i++)
	{
		printf("giorno %d ", i+1);
		switch (num_giorno_settimana % 7)
		{
			case 0:
				printf("lunedi'\n");
				break;
			case 1:
				printf("martedi'\n");
				break;
			case 2:
				printf("mercoledi'\n");
				break;
			case 3:
				printf("giovedi'\n");
				break;
			case 4:
				printf("venerdi'\n");
				break;
			case 5:
				printf("sabato\n");
				break;
			case 6:
				printf("domenica\n");
				break;
		}
		num_giorno_settimana++;
	}
	return 0;
}

