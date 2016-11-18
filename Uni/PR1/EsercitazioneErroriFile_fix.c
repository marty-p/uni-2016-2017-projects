#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 10
#define MIN 10
#define MAX 20

int main() {
    int x, flag, i;
    int A[DIM] = {};

    srand(time(NULL));

    /**
     Trova gli errori.
    */
    //la seguente porzione di codice chiede un intero e si assicura che l'intero
    //sia maggiore di 1
    do{
        printf("Inserisci un numero: ");
        scanf("%d", &x);
    } while(x <= 1);

    //la seguente porzione di codice controlla se x e' un numero primo
    flag = 0;
    for (i=2; i<x && flag == 0; ++i) {
        if ((x % i) == 0) {
            flag = 1;
        }
    }
    if (flag != 0) {
        printf("%d non e' primo\n", x);
    }
    else {
        printf("%d e' primo\n", x);
    }

    //la seguente porzione di codice inizializza l'array A con valori casuali
    // compresi tra MIN e MAX (estremi inclusi)
    for (i=0; i<DIM; i++){
        A[i] = MIN + rand()%(MAX-MIN+1);
    }

    //la seguente porzione di codice stampa l'array A invertito
    for (i = DIM-1; i >= 0; --i){
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
