#include <stdio.h>
#include <stdlib.h>
/*5. Scrivere una funzione che esegua l'acquisizione di un numero e il controllo che il numero si trovi all'interno di un
determinato intervallo (min, max), mediante l'acquisizione ripetuta del numero. La funzione deve restituire sempre un valore
compreso tra min e max.*/
#define MIN 1
#define MAX 100
int acquisizioneNumero(int min, int max);
int main()
{
    printf("Numero: %d\n", acquisizioneNumero(MIN, MAX));
    return 0;
}
int acquisizioneNumero(int min, int max)
{
    int nInput;
    do
    {
        printf("Inserisci un numero tra %d e %d:\n", min, max);
        scanf("%d", &nInput);
    } while (nInput < min || nInput > max);
    return nInput;
}

