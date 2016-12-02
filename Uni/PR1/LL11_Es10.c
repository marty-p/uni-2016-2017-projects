#include <stdio.h>
#include <stdlib.h>
/*10. Definire una struttura che consente di gestire un elemento di una rubrica telefonica; i
campi da utilizzare sono a vostra discrezione, l’unico vincolo è la presenza del nome e del
numero di telefono, ambedue memorizzati come stringhe. Gestire quindi un array di elementi,
prevedendo la possibilità di inserire, modificare, visualizzare, ricercare e cancellare elementi
dalla rubrica stessa.
*/
#define DIM_RUBRICA 5
#define S 50
#define N_TELEFONO 10
#define NL "\n"
#define TAB "\t"
typedef struct
{
    int giorno;
    int mese;
    int anno;
} DataNascita;

typedef enum {amici, parenti, sconosciuti, personefalze} Categoria;

typedef struct
{
    char nome[S+1];
    char cognome[S+1];
    // int numero;
    char telefono[N_TELEFONO+1];
    DataNascita data;
    Categoria categoria;
} Contatto;

DataNascita acquisisciDataNascita(void);
void acquisisciDataNascitaPtr(DataNascita * pData);
void stampaDataNascita(DataNascita d);
void stampaDataNascitaPtr(DataNascita * pData);

Contatto acquisisciContatto(void);
void acquisisciContattoPtr(Contatto* pContatto);
void stampaContatto(Contatto c);
void stampaContattoPtr(Contatto * pContatto);
//void stampaDimensioneContatto(Contatto c[]);
//void stampaDimensioneContatto(Contatto c[DIM_RUBRICA]);

int main()
{
    // Contatto contatto = acquisisciContatto();
    // stampaContatto(contatto);
    //Contatto contatto;
    //acquisisciContattoPtr(&contatto);
    //stampaContattoPtr(&contatto);
    Contatto c[DIM_RUBRICA];
    int i;
    //printf("#c: %d\n", sizeof(c)/sizeof(Contatto));
    //stampaDimensioneContatto(c);
    for (i=0; i<DIM_RUBRICA; i++)
        acquisisciContattoPtr(&c[i]);
        //acquisisciContattoPtr(c+i);
    return 0;
}

/*void stampaDimensioneContatto(Contatto c[])
{
    printf("c: %d\n", sizeof(c));
}*/

/*void stampaDimensioneContatto(Contatto c[DIM_RUBRICA])
{
    printf("c: %d\n", sizeof(c));
}*/

DataNascita acquisisciDataNascita(void)
{
    DataNascita d = {};
    printf("Giorno:\n");
    scanf("%d", &d.giorno);

    printf("Mese:\n");
    scanf("%d", &d.mese);

    printf("Anno:\n");
    scanf("%d", &d.anno);

    while(getchar()!='\n');

    return d;
}

void acquisisciDataNascitaPtr(DataNascita * pData)
{
    printf("Giorno:\n");
    scanf("%d", &pData->giorno);

    printf("Mese:\n");
    scanf("%d", &pData->mese);

    printf("Anno:\n");
    scanf("%d", &pData->anno);

    while(getchar()!='\n');
}

void stampaDataNascita(DataNascita d)
{
    printf("Data: %d/%d/%d"NL, d.anno, d.mese, d.giorno);
}

void stampaDataNascitaPtr(DataNascita * pData)
{
    printf("Data: %d/%d/%d"NL, pData->anno, pData->mese, pData->giorno);
}

Contatto acquisisciContatto(void)
{
    Contatto c = {};

    printf("Nome:\n");
    scanf("%50s", c.nome);
    while(getchar()!='\n');

    printf("Cognome:\n");
    scanf("%50s", c.cognome);
    while(getchar()!='\n');

    printf("N. Telefono:\n");
    scanf("%50s", c.telefono);
    while(getchar()!='\n');

    c.data = acquisisciDataNascita();

    printf("Inserisci categoria amici:"NL TAB"0:amici,"NL TAB"1:parenti,"NL TAB"2:sconosciuti,"NL TAB"3:personefalze\n");
    //scanf("%d", (int*)&c.categoria);
    scanf("%u", &c.categoria);
    while(getchar()!='\n');

    return c;
}

void acquisisciContattoPtr(Contatto * pContatto)
{
    printf("Nome:\n");
    scanf("%50s", pContatto->nome);
    while(getchar()!='\n');

    printf("Cognome:\n");
    scanf("%50s", pContatto->cognome);
    while(getchar()!='\n');

    printf("N. Telefono:\n");
    scanf("%50s", pContatto->telefono);
    while(getchar()!='\n');

    acquisisciDataNascitaPtr(&pContatto->data);

    printf("Inserisci categoria amici:"NL TAB"0:amici,"NL TAB"1:parenti,"NL TAB"2:sconosciuti,"NL TAB"3:personefalze\n");
    //scanf("%d", (int*)&pContatto->categoria);
    scanf("%u", &pContatto->categoria);
    while(getchar()!='\n');
}

void stampaContatto(Contatto c)
{
    printf("Nome: %s"NL"Cognome: %s"NL"N. Telefono: %s"NL, c.nome, c.cognome, c.telefono);
    stampaDataNascita(c.data);
    printf("Categoria: %d"NL, c.categoria);
}

void stampaContattoPtr(Contatto * pContatto)
{
    printf("Nome: %s"NL"Cognome: %s"NL"N. Telefono: %s"NL, pContatto->nome, pContatto->cognome, pContatto->telefono);
    stampaDataNascitaPtr(&(pContatto->data));
    printf("Categoria: %d"NL, pContatto->categoria);
}

