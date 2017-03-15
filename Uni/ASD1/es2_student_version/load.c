/* NON MODIFICARE QUESTO FILE!!!
 * Funzione che carica da file un array di DIM elementi in cui effettuare la ricerca
 */

#include "load.h"

int* loadFromFile(int numtest)
{
    FILE *fp;
    int* array = NULL;
    
    switch(numtest)
    {
        case 10:
            fp = fopen("test/test10.txt", "r");
            if(!fp)
            {
                printf("caricamento test fallito\n");
                return NULL;
            }
            break;
            
        case 50:
            fp = fopen("test/test50.txt", "r");
            if(!fp)
            {
                printf("caricamento test fallito\n");
                return NULL;
            }
            break;
            
        case 100:
            fp = fopen("test/test100.txt", "r");
            if(!fp)
            {
                printf("caricamento test fallito\n");
                return NULL;
            }
            break;
            
        case 1000:
            fp = fopen("test/test1000.txt", "r");
            if(!fp)
            {
                printf("caricamento test fallito\n");
                return NULL;
            }
            break;
            
        case 10000:
            fp = fopen("test/test10000.txt", "r");
            if(!fp)
            {
                printf("caricamento test fallito\n");
                return NULL;
            }
            break;
            
        case 100000:
            fp = fopen("test/test100000.txt", "r");
            if(!fp)
            {
                printf("caricamento test fallito\n");
                return NULL;
            }
            break;
            
        case 500000:
            fp = fopen("test/test500000.txt", "r");
            if(!fp)
            {
                printf("caricamento test fallito\n");
                return NULL;
            }
            break;
            
        default:
            printf("test non trovato\n");
            return NULL;
    }
    
    if(fp)
    {
        array = (int*)malloc(numtest * sizeof(int));

        int i=0;
        int num;
        while(fscanf(fp, "%d", &num) == 1) 
        {
            array[i] = num;
            i++;
        }
        fclose(fp);
    }
    
    return array;
}

