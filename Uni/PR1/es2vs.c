/** INIZIO INCLUDE E DEFINE DOCENTE **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define N_TERRENI 40    //Numero terreni
#define MAX_STRINGA 25  //Dimensione massima stringa nome giocatore e nome terreno
#define GIOCATORI 4     //Numero giocatori
/** FINE INCLUDE E DEFINE DOCENTE **/

/** INIZIO INCLUDE E DEFINE STUDENTE **/
/* Potrebbe non essere necessaria alcuna define e/o include aggiuntiva. */
#define MIN_ES2 1
#define MAX_ES2 10
#define MLT_ES2 100
/** FINE INCLUDE E DEFINE STUDENTE **/

int main(){
    /** INIZIO VARIABILI DOCENTE **/
    int i;
    int idTerreno=0, idGiocatore=0, totValore=0, indiceMax=0; //L'utilizzo di queste variabili e' definito nel testo degli esercizi
    char sceltaUt='N';

    /**
        Esercizio 1: Dichiarazione e inizializzazione array di stringhe - punteggio 1/10
        Dichiarare un array di stringhe 'giocatori' con numero righe pari a 'GIOCATORI' e
        numero colonne pari a 'MAX_STRINGA'.
        Inizializzarlo poi con i valori "Fabio","Riccardo", "Alessandro" e "Giammy".
    **/
    /** INIZIO CODICE STUDENTE ESERCIZIO 1 **/
    //Codice studente...
	char giocatori[GIOCATORI][MAX_STRINGA] = {"Fabio","Riccardo", "Alessandro", "Giammy"};
    /** FINE   CODICE STUDENTE ESERCIZIO 1 **/

    int terreniAcquistati[N_TERRENI];  //Ogni cella del vettore contiene l'ID del proprietario del terreno.
    int valoriTerreni[N_TERRENI];      //Valore in euro dei singoli terreni

    //Questo vettore di stringhe contiene i nomi di tutti i terreni del tabellone
    char terreni[N_TERRENI][MAX_STRINGA]={
                      "VIA!",                   "VICOLO CORTO",         "PROBABILITA'",        "VICOLO STRETTO",
                      "TASSA",                  "STAZIONE SUD",         "BASTIONI GRAN SASSO", "IMPREVISTI",
                      "VIALE MONTEROSA",        "VIALE VESUVIO",        "TRANSITO",            "VIA ACCADEMIA",
                      "SOCIETA ELETTRICA",      "CORSO ATENEO",         "PIAZZA UNIVERSITA'",  "STAZIONE OVEST",
                      "VIA VERDI",              "PROBABILITA'",         "CORSO RAFFAELLO",     "PIAZZA DANTE",
                      "PARCHEGGIO GRATUITO",    "VIA MARCO POLO",       "IMPREVISTI",          "CORSO MAGELLANO",
                      "LARGO COLOMBO",          "STAZIONE NORD",        "VIALE COSTANTINO",    "VIALE TRAIANO",
                      "SOCIETA ACQUA POTABILE", "PIAZZA GIULIO CESARE", "VAI IN PRIGIONE",     "VIA ROMA",
                      "CORSO IMPERO",           "PROBABILITA'",         "LARGO AUGUSTO",       "STAZIONE EST",
                      "IMPREVISTI",             "VIALE DEI GIARDINI",   "TASSA SUL LUSSO",     "PARCO DELLA VITTORIA"
    };

    //Ogni cella del vettore contiene un valore booleano ('true' se il terreno e' acquistabile, 'false' in caso contrario)
    _Bool terreniAcquistabili[N_TERRENI]={false,    true,   false,  true,
                                          false,    true,   true,   false,
                                          true,     true,   false,  true,
                                          true,     true,   true,   true,
                                          true,     false,  true,   true,
                                          false,    true,   false,  true,
                                          true,     true,   true,   true,
                                          true,     true,   false,  true,
                                          true,     false,  true,   true,
                                          false,    true,   false,  true
    };
    /** FINE VARIABILI DOCENTE **/

    /** INIZIO VARIABILI STUDENTE **/
    /* Potrebbe non essere necessaria alcuna variabile aggiuntiva. */
    /** FINE VARIABILI STUDENTE **/
    srand(time(NULL));
    /*
        Questo ciclo permette di assegnare in maniera casuale un valore e un proprietario ai terreni.
        In caso di terreni non vendibili assegna 0 al valore della proprieta' e -1 al valore del proprietario.
    */
    for(i=0;i<N_TERRENI; i++){
        if(terreniAcquistabili[i]==true){
            /**
                Esercizio 2: Generazione casuale - punteggio 1/10
                Generare un numero casuale tra 100 e 1000 che sia multiplo di 100
                ed assegnarlo alla cella i-esima del vettore 'valoriTerreni'.
            **/
            /** INIZIO CODICE STUDENTE ESERCIZIO 2 **/
            //Codice studente...
			valoriTerreni[i] = (MIN_ES2 + rand() % (MAX_ES2 - MIN_ES2 +1)) * MLT_ES2;
            /** FINE   CODICE STUDENTE ESERCIZIO 2 **/
            terreniAcquistati[i]=rand()%4;
        }
        else{
            valoriTerreni[i]=0;
            terreniAcquistati[i]=-1;
        }
    }

    /**
        Esercizio 3: Ciclo FOR - punteggio 2/10
        Mediante l'utilizzo di un FOR stampare per ogni terreno:
        -   il nome della proprieta';
        -   il valore di mercato;
        -   il nome del proprietario.
        ATTENZIONE: alcuni terreni non sono vendibili (acquistabili), quindi per essi dovra' essere stampato:
        -   il nome della proprieta';
        -   la scritta "Non vendibile" al posto del prezzo di mercato;
        -   la scritta "Banco" al posto del nome proprietario

        La stampa risultante dei singoli terreni sara' qualcosa di simile a:
        VIA!:                 Non vendibile. Proprietario: Banco
        VICOLO CORTO:         800 euro.      Proprietario: Riccardo
        ...................................................
        TASSA SUL LUSSO:      Non vendibile. Proprietario: Banco
        PARCO DELLA VITTORIA: 900 euro.      Proprietario: Alessandro
    **/
    /** INIZIO CODICE STUDENTE ESERCIZIO 3 **/
    //Codice studente...
    for (i=0; i<N_TERRENI; i++)
	{
		if (terreniAcquistabili[i]==true)
            // printf("Nome terreno: \t\t%s\nValore di mercato: \t%d euro\nProprietario: \t\t%s\n", terreni[i], valoriTerreni[i], giocatori[terreniAcquistati[i]]);
			printf("[%02d] %-30s euro %-15d Proprietario: %s\n", i, terreni[i], valoriTerreni[i], giocatori[terreniAcquistati[i]]);
        else
            // printf("Nome terreno: \t\t%s\nValore di mercato: \tNon vendibile\nProprietario: \t\tBanco\n", terreni[i]);
			printf("[%02d] %-30s %-20s Proprietario: %s\n", i, terreni[i], "Non vendibile", "Banco");
	}
    /** FINE   CODICE STUDENTE ESERCIZIO 3 **/


    /*
        Questo ciclo permette di stampare i dettagli di un singolo terreno sulla base
        dell'input dell'utente per un numero di volte definito dall'utente stesso.
    */
    do{
        /**
            Esercizio 4: Ciclo WHILE/DO-WHILE - punteggio 1/10
            Mediante l'utilizzo di un ciclo WHILE o DO-WHILE (scegliere il costrutto piu' attinente)
            chiedere all'utente di inserire il codice di un terreno e verificare che esso sia ammesso.
            Il codice terreno dovra' essere assegnato alla variabile 'idTerreno' precedentemente dichiarata.
            HINT: usare la getchar() dopo l'acquisizione dell'input
        **/
        /** INIZIO CODICE STUDENTE ESERCIZIO 4 **/
        //Codice studente...
		do {
			printf("Immetti il codice di un terreno: (0-%d)\n", N_TERRENI-1);
			scanf("%d", &idTerreno);
			getchar();
		} while (idTerreno < 0 || idTerreno >= N_TERRENI);
        /** FINE   CODICE STUDENTE ESERCIZIO 4 **/

        /*
            Questa selezione permette di stampare opportunatamente i dettagli sul terreno
            in base alla caratteristica non/vendibile.
        */
        if(valoriTerreni[idTerreno]>0)
            printf("Nome terreno: \t\t%s\nValore di mercato: \t%d euro\nProprietario: \t\t%s\n", terreni[idTerreno], valoriTerreni[idTerreno], giocatori[terreniAcquistati[idTerreno]]);
        else
            printf("Nome terreno: \t\t%s\nValore di mercato: \tNon vendibile\nProprietario: \t\tBanco\n", terreni[idTerreno]);

        /**
            Esercizio 5: Ciclo WHILE/DO-WHILE - punteggio 1/10
            Mediante l'utilizzo di un ciclo WHILE o DO-WHILE (scegliere il costrutto piu' attinente)
            chiedere all'utente di indicare o meno la volonta' di stampare i dati di un altro terreno.
            La scelta dovra' essere memorizzata nella variabile 'sceltaUt' e sono ammessi ESCLUSIVAMENTE
            i valori 'S' ed 'N'. In caso contrario dovra' essere chiesto nuovamente l'inserimento.
            HINT: usare la getchar() dopo l'acquisizione dell'input
        **/
        /** INIZIO CODICE STUDENTE ESERCIZIO 5 **/
        //Codice studente...
		do {
			printf("Immetti S o N per printare un altro terreno:\n");
			scanf("%c", &sceltaUt);
			getchar();
		} while (sceltaUt != 'S' && sceltaUt != 'N');
        /** FINE   CODICE STUDENTE ESERCIZIO 5 **/
    }while(sceltaUt!='N');

    /*
        Questo ciclo permette di stampare i dettagli dei terreni di un singolo giocatore sulla base
        dell'input dell'utente per un numero di volte definito dall'utente stesso.
    */
    do{
        //Questo ciclo permette l'acquisizione ed il controllo dell'input sull'ID del giocatore
        do{
            printf("\nInserisci codice giocatore: ");
            scanf("%d", &idGiocatore);
            getchar();
            if(idGiocatore<0 || idGiocatore>=GIOCATORI)
                printf("Scelta non disponibile.");
        }while(idGiocatore<0 || idGiocatore>=GIOCATORI);

        printf("Elenco terreni di %s\n", giocatori[idGiocatore]);
        /**
            Esercizio 6: Ciclo FOR e sommatoria - punteggio 2/10
            Implementare la porzione di codice necessaria a stampare tutte le proprieta' del giocatore indicato precedentemente
            (il cui indice e' memorizzato in 'idGiocatore') e che calcoli la somma dei valori di esse.
            Il valore dovra' essere memorizzato all'interno della variabile 'totValore'.
            Si ricorda che:
            -   il vettore di stringhe 'terreni' contiene i nomi delle proprieta';
            -   il vettore 'valoreTerreni' il valore delle proprieta';
            -   il vettore 'terreniAcquistati' il valore relativo ai proprietari.
        **/
        /** INIZIO CODICE STUDENTE ESERCIZIO 6 **/
        //Codice studente...
		totValore = 0;
		for (i=1; i<N_TERRENI; i++)
		{
			if (terreniAcquistabili[i]==true && terreniAcquistati[i] == idGiocatore)
			{
				printf("[%02d] %-30s euro %-15d\n", i, terreni[i], valoriTerreni[i]);
				totValore += valoriTerreni[i];
			}
		}
		printf("Valore totale: %d euro\n", totValore);
        /** FINE   CODICE STUDENTE ESERCIZIO 6 **/

        //Questo ciclo permette l'acquisizione ed il controllo sulla volonta' di stampare i dettagli di un nuovo giocatore
        do{
            printf("\nVuoi vedere i terreni di un altro giocatore? (S/N)");
            scanf("%c", &sceltaUt);
            getchar();
            if(sceltaUt!='N' && sceltaUt!='S')
                printf("Scelta non disponibile.");
        }while(sceltaUt!='N' && sceltaUt!='S');

    }while(sceltaUt!='N');

    /**
        Esercizio 7: Ciclo FOR e sommatoria - punteggio 1/10
        Implementare la porzione di codice necessaria a stampare il nome del terreno piu' costoso
        ed il suo valore.
        HINT: usare la variabile 'indiceMax' per contenere l'indice del valore piu' costoso
    **/
    /** INIZIO CODICE STUDENTE ESERCIZIO 7 **/
    //Codice studente...
	indiceMax = 0;
    for (i=1; i<N_TERRENI; i++)
		if (valoriTerreni[indiceMax] < valoriTerreni[i])
			indiceMax = i;

	// printf("Terreno piu' costoso:\n");
	// printf("%-30s euro %-15d Proprietario: %s\n", terreni[indiceMax], valoriTerreni[indiceMax], giocatori[terreniAcquistati[indiceMax]]);

	printf("Terreni piu' costosi:\n");
    for (i=1; i<N_TERRENI; i++)
		if (valoriTerreni[indiceMax] == valoriTerreni[i])
			printf("%-30s euro %-15d Proprietario: %s\n", terreni[i], valoriTerreni[i], giocatori[terreniAcquistati[i]]);
    /** FINE   CODICE STUDENTE ESERCIZIO 7 **/

    return 0;
}
