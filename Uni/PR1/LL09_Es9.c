#include <stdio.h>
#include <stdlib.h>
/*9. Scrivere una funzione che, preso in ingresso un intero, verifichi se sia compreso nel range 1 - 7 e, se sì, visualizzi il giorno
della settimana corrispondente (1=lunedì, 2=martedì ...). La funzione dovrà poi restituire TRUE se il parametro è compreso
nel range 1 - 7 , FALSE altrimenti. Visualizzare quindi dal main l'eventuale messaggio di errore, dopo aver verificato che la
funzione sia stata eseguita correttamente.*/
#define TRUE 1
#define FALSE 0
#define LUNEDI 1
#define MARTEDI 2
#define MERCOLEDI 3
#define GIOVEDI 4
#define VENERDI 5
#define SABATO 6
#define DOMENICA 7
int day_of_week(int n);
int main()
{
    int nInput;
    printf("Inserisci un numero (giorno della settimana):\n");
    scanf("%d", &nInput);
    if (day_of_week(nInput)==FALSE)
        printf("ERRORE: Il numero %d non e' un giorno della settimana!\n", nInput);
    return 0;
}
int day_of_week(int n)
{
    char giorni[7][20+1] = {
        "lunedi'",
        "martedi'",
        "mercoledi'",
        "giovedi'",
        "venerdi'",
        "sabato",
        "domenica",
    };
    if (LUNEDI <= n && n <= DOMENICA)
    {
        // way1
        switch (n)
        {
        case LUNEDI:
            printf("lunedi'\n");
            break;
        case MARTEDI:
            printf("martedi'\n");
            break;
        case MERCOLEDI:
            printf("mercoledi'\n");
            break;
        case GIOVEDI:
            printf("giovedi'\n");
            break;
        case VENERDI:
            printf("venerdi'\n");
            break;
        case SABATO:
            printf("sabato\n");
            break;
        case DOMENICA:
            printf("domenica\n");
            break;
        }
        // way2
        printf("%s\n", giorni[n-1]);
        return TRUE;
    }
    return FALSE;
}
