#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// 1. LISTE CONCATENATE SEMPLICI (LINEARI)
// Struttura:

typedef struct nodo{
	int info; // Variabile contenente l'informazione, può essere di qualsiasi tipo
	struct nodo* next;
} Nodo;

// Caratteristiche:
// • Ogni nodo contiene un campo “informazione” e un campo “puntatore al nodo
// successivo” (next);
// • Il primo elemento della lista è puntato da un puntatore a nodo di tipo Nodo*;
// quando la lista è vuota, questo puntatore è settato a NULL (esempio di
// dichiarazione e inizializzazione di una lista: Nodo* lista = NULL;);
// • L'ultimo nodo della lista ha il campo “next” settato a NULL.
// Funzioni da implementare:
// • Inserimento in testa;
// Prototipo:
Nodo* inserisciNodoInTesta(Nodo* first, int value);
// • Stampa di una lista, sia iterativa che ricorsiva;
// Prototipi:
void stampaLista(Nodo* first);
void stampaListaRicorsiva(Nodo* first);
// • Deallocazione di una lista, sia iterativa che ricorsiva;
// Prototipi:
void eliminaLista(Nodo* first);
void eliminaListaRicorsiva(Nodo* first);
// • Inserimento in coda, solo iterativo;
// Prototipo:
Nodo* inserisciNodoInCoda(Nodo* first, int value);
// • Dimensione di una lista, sia ricorsiva che iterativa;
// Prototipi:
int dimensioneLista(Nodo* first);
int dimensioneListaRicorsiva(Nodo* first);
// • Restituzione dell'n-esimo nodo di una lista, sia iterativa che ricorsiva (il primo
// nodo della lista avrà indice 0, gestire tutti i casi di errore come n negativo o n
// maggiore del numero di elementi della lista);
// Prototipi:
Nodo* restituisciNodo(Nodo* first, int n);
Nodo* restituisciNodoRicorsiva(Nodo* first, int n);
// • Eliminazione in testa:
// Prototipo:
Nodo* eliminaNodoInTesta(Nodo* first);
// 1
// • Eliminazione dell'n-esimo nodo di una lista, solo iterativa;
// Prototipo:
Nodo* eliminaNodo(Nodo* first, int n);
// • Ricerca nodo, solo iterativa (cercare e restituire il nodo all'interno della lista
// contenente il valore cercato);
// Prototipo:
Nodo* cercaNodo(Nodo* first, int value);
// • Inserimento ordinato, solo iterativa: inserire continuamente elementi nella lista
// facendo in modo che la lista sia ordinata in modo crescente;
// Prototipo:
Nodo* inserisciNodoListaOrdinata(Nodo* first, int value);

// Extra
void stampaInfo(int value);

int main()
{
	Nodo * testaListaRegali = NULL;
	Nodo * nodoRestituito = NULL;
	int i;

	srand(time(NULL));

	for (i = 0; i < 10; i++)
	{
		testaListaRegali = inserisciNodoInCoda(testaListaRegali, i);
		// testaListaRegali = inserisciNodoInCoda(testaListaRegali, 9-i);
		// testaListaRegali = inserisciNodoInTesta(testaListaRegali, i);
		// testaListaRegali = inserisciNodoListaOrdinata(testaListaRegali, 9-i);
		// testaListaRegali = inserisciNodoListaOrdinata(testaListaRegali, 100 + rand() % (999-100+1));
		// testaListaRegali = inserisciNodoListaOrdinata(testaListaRegali, i);
	}

	// testaListaRegali = eliminaNodoInTesta(testaListaRegali);
	testaListaRegali = eliminaNodo(testaListaRegali, 1);
	// testaListaRegali = eliminaNodo(testaListaRegali, 7);
	// for (i = 0; i < 10; i++)
	// {
		// testaListaRegali = eliminaNodoInTesta(testaListaRegali);
		// testaListaRegali = eliminaNodo(testaListaRegali, 0);
		// testaListaRegali = eliminaNodo(testaListaRegali, i);
		// testaListaRegali = eliminaNodo(testaListaRegali, 9-i);
	// }

	printf("# Elementi: %d\n", dimensioneLista(testaListaRegali));
	// printf("# Elementi: %d\n", dimensioneListaRicorsiva(testaListaRegali));

	stampaLista(testaListaRegali);
	// stampaListaRicorsiva(testaListaRegali);

	nodoRestituito = restituisciNodo(testaListaRegali, 3);
	// nodoRestituito = restituisciNodoRicorsiva(testaListaRegali, 3);
	if (nodoRestituito != NULL)
		printf("Trova elemento 3: %d\n", nodoRestituito->info);
	else
		printf("elemento 3 non trovato\n");

	nodoRestituito = cercaNodo(testaListaRegali, 3);
	if (nodoRestituito != NULL)
		printf("Trova value 3: %d\n", nodoRestituito->info);
	else
		printf("value 3 non trovato\n");

	eliminaLista(testaListaRegali);
	// eliminaListaRicorsiva(testaListaRegali);
	return 0;
}

Nodo* inserisciNodoInTesta(Nodo* first, int value)
{
	Nodo * nuovoNodo=NULL;

	nuovoNodo = malloc(sizeof(Nodo));
	if (nuovoNodo==NULL)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		nuovoNodo->info = value;
		nuovoNodo->next = first;
	}

	return nuovoNodo;

}

void stampaLista(Nodo* first)
{
	while (first != NULL)
	{
		stampaInfo(first->info);
		first = first->next;
	}
}

void stampaListaRicorsiva(Nodo* first)
{
	if (first != NULL)
	{
		stampaInfo(first->info);
		stampaListaRicorsiva(first->next);
	}
}

void eliminaLista(Nodo* first)
{
	Nodo * tmp = NULL;
	while (first != NULL)
	{
		tmp = first->next;
		free(first);
		first = tmp;
	}
}

void eliminaListaRicorsiva(Nodo* first)
{
	if (first != NULL)
	{
		eliminaListaRicorsiva(first->next);
		free(first);
	}
}

Nodo* inserisciNodoInCoda(Nodo* first, int value)
{
	Nodo * tmp = first;
	if (first==NULL)
		return inserisciNodoInTesta(first, value);

	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = inserisciNodoInTesta(NULL, value);

	return first;
}

int dimensioneLista(Nodo* first)
{
	int count = 0;
	while (first != NULL)
	{
		count++;
		first = first->next;
	}
	return count;
}

int dimensioneListaRicorsiva(Nodo* first)
{
	if (first != NULL)
	{
		return 1 + dimensioneListaRicorsiva(first->next);
	}
	return 0;
}

Nodo* restituisciNodo(Nodo* first, int n)
{
	int count = 0;

	// check indice negativo:
	if (n < 0)
		return NULL;

	while (first != NULL && count < n)
	{
		count++;
		first = first->next;
	}

	// check indice overflow:
	if (count < n)
		return NULL;

	return first;
}

Nodo* restituisciNodoRicorsiva(Nodo* first, int n)
{
	// check indice negativo
	if (n < 0)
		return NULL;

	if (first != NULL)
	{
		if (n == 0)
			return first;
		else
			return restituisciNodoRicorsiva(first->next, n-1);
	}

	// check indice overflow
	return NULL;
}

Nodo* eliminaNodoInTesta(Nodo* first)
{
	Nodo * tmp = first;
	if (first != NULL)
	{
		tmp = first->next;
		free(first);
	}
	return tmp;
}

Nodo* eliminaNodo(Nodo* first, int n)
{
	int count = 0;
	Nodo * tmp = first;
	Nodo * prevtmp = first;

	// check indice negativo:
	if (n < 0)
		return first;

	// check se indice sia testa:
	if (n==0)
		return eliminaNodoInTesta(first);

	while (tmp != NULL && count <= n)
	{
		if (count==n)
		{
			prevtmp->next = tmp->next;
			free(tmp);
			return first;
		}
		else
		{
			prevtmp = tmp;
			tmp = tmp->next;
			count++;
		}
	}

	return first;
}

Nodo* cercaNodo(Nodo* first, int value)
{
	while (first != NULL)
	{
		if (first->info == value)
			return first;
		first = first->next;
	}
	return NULL; // anche ritornando first qua, apparirebbe comunque come NULL
}

Nodo* inserisciNodoListaOrdinata(Nodo* first, int value)
{
	Nodo * tmp = NULL;
	Nodo * prevtmp = NULL;

	if (first==NULL)
		return inserisciNodoInTesta(first, value);
	else
	{
		tmp = first;
		prevtmp = NULL;
	}

	while (tmp != NULL && value > tmp->info)
	{
		prevtmp = tmp;
		tmp = tmp->next;
	}

	if (prevtmp==NULL)
		return inserisciNodoInTesta(tmp, value);
	prevtmp->next = inserisciNodoInTesta(tmp, value);

	return first;
}

// Extra
void stampaInfo(int value)
{
	printf("%d\n", value);
}
//

