#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_NOME 50
#define DIM_HEAP 50

//stuttura che rappresenta un Pronto soccorso
typedef struct
{
	int numeroB;
	int numeroG;
	int numeroV;
	int numeroR;
} ProntoSoccorso;

//enumerazione che rappresenta i codici del pronto soccorso
#define CODICE_NUM 4
typedef enum {BIANCO, VERDE, GIALLO, ROSSO} Codice;

//struttura che rappresenta un Paziente
typedef struct
{
	char nome[DIM_NOME];
	Codice codice;
	int ordine;
} Paziente;

typedef struct
{
	Paziente heap[DIM_HEAP];
	int n;
} ListaPazienti;

//funzione che chiede i dati relativi ad un nuovo paziente e lo restituisce (con la priorita' gia' impostata) pronto per essere inserito nella coda con priorita' (heap)
Paziente nuovoPaziente(ProntoSoccorso *ps);
Paziente nuovoPazienteNoInput(ProntoSoccorso *ps, const char* nome, Codice codice);
void print_raw_heap(const ListaPazienti * lp);
void insert_heap(ListaPazienti * lp, Paziente item);
Paziente delete_heap(ListaPazienti * lp);
const char * get_codice_name(Codice codice);
void stampaListaPazienti(const ListaPazienti * lp);
void stampaPaziente(const Paziente * p);
int controlloPriorita(const Paziente * p1, const Paziente * p2); // -1 minore, 0 uguale, +1 maggiore

int main()
{
	//inizializzazione pronto soccorso
	ProntoSoccorso ps = {};
	//ps.numeroB = ps.numeroG = ps.numeroV = ps.numeroR = 0;

	//inizializzazione della Coda con priorita'
	ListaPazienti lp = {};
	//Paziente codaPrio[DIM_HEAP];
	//int dim_coda = 0;
	stampaListaPazienti(&lp);
	//insert_heap(&lp, nuovoPaziente(&ps));
	//insert_heap(&lp, nuovoPaziente(&ps));
	//insert_heap(&lp, nuovoPaziente(&ps));
	//insert_heap(&lp, nuovoPaziente(&ps));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek1", BIANCO));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek2", BIANCO));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek3", BIANCO));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek4", BIANCO));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek5", BIANCO));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek6", ROSSO));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek7", VERDE));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek8", GIALLO));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek9", GIALLO));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek10", GIALLO));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek11", VERDE));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek12", ROSSO));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek13", VERDE));
	insert_heap(&lp, nuovoPazienteNoInput(&ps, "kek14", ROSSO));
	stampaListaPazienti(&lp);
	print_raw_heap(&lp);
	delete_heap(&lp);
	delete_heap(&lp);
	delete_heap(&lp);
	delete_heap(&lp);
	delete_heap(&lp);
	delete_heap(&lp);
	delete_heap(&lp);
	delete_heap(&lp);
	stampaListaPazienti(&lp);
	print_raw_heap(&lp);

	return 0;
}

int controlloPriorita(const Paziente * p1, const Paziente * p2)
{
	if (p1==NULL || p2==NULL)
		return 0;
	if (p1->codice < p2->codice)
		return -1;
	else if (p1->codice > p2->codice)
		return 1;
	return 0; // implica (p1->codice==p2->codice)
}

Paziente nuovoPaziente(ProntoSoccorso *ps)
{
	Paziente p = {};

	printf("\nNome paziente -> ");
	scanf("%49[^\n]s", p.nome);
	getchar();

	do
	{
		printf("\nCodice paziente (0 = bianco, 1 = verde, 2 = giallo, 3 = rosso)-> ");
		scanf("%u", &p.codice);
		getchar();

		if(p.codice < BIANCO || p.codice > ROSSO)
		{
			printf("\nCodice non valido");
		}
	}
	while (p.codice < BIANCO || p.codice > ROSSO);

	if(p.codice == BIANCO)
	{
		ps->numeroB++;
		p.ordine = ps->numeroB;
	}
	else if(p.codice == GIALLO)
	{
		ps->numeroG++;
		p.ordine = ps->numeroG;

	}
	else if (p.codice == VERDE)
	{
		ps->numeroV++;
		p.ordine = ps->numeroV;
	}
	else
	{
		ps->numeroR++;
		p.ordine = ps->numeroR;
	}

	return p;
}

Paziente nuovoPazienteNoInput(ProntoSoccorso *ps, const char* nome, Codice codice)
{
	Paziente p = {};
	strcpy(p.nome, nome);
	p.codice = codice;

	if(p.codice == BIANCO)
	{
		ps->numeroB++;
		p.ordine = ps->numeroB;
	}
	else if(p.codice == GIALLO)
	{
		ps->numeroG++;
		p.ordine = ps->numeroG;

	}
	else if (p.codice == VERDE)
	{
		ps->numeroV++;
		p.ordine = ps->numeroV;
	}
	else
	{
		ps->numeroR++;
		p.ordine = ps->numeroR;
	}

	return p;
}

void print_raw_heap(const ListaPazienti * lp)
{
	int i;
	if (lp==NULL)
		return;
	for (i=1; i<=lp->n; i++)
		printf("%3d ", lp->heap[i].codice);
	printf("\n");
}

void insert_heap(ListaPazienti * lp, Paziente item)
{
    int i;
    if (lp==NULL)
    	return;
	// inserisce un nuovo item in un heap di n elementi
	if (lp->n == DIM_HEAP-1)
	{
		printf("L'heap e' pieno\n");
		return;
	}
	lp->n++;
	i = lp->n;
	while (i != 1 && controlloPriorita(&item, &lp->heap[i/2])>0)
	{
		lp->heap[i] = lp->heap[i/2];
		i = i/2;
	}
	lp->heap[i] = item;
}

Paziente delete_heap(ListaPazienti * lp)
{
// cancella e restituisce l’elemento radice in un heap di n elementi
	Paziente * item = &lp->heap[1];
	Paziente * temp = &lp->heap[lp->n];
	int padre = 1;
	int figlio = 2;
	if (lp->n == 0)
	{
		printf("L'heap e' vuoto\n");
		return;
	}
	lp->n--;
	while (figlio <= lp->n)
	{
		if (figlio < lp->n && controlloPriorita(&lp->heap[figlio], &lp->heap[figlio+1])<0)
			figlio = figlio+1;
		if (controlloPriorita(temp, &lp->heap[figlio])>=0)
			break;
		lp->heap[padre] = lp->heap[figlio];
		padre = figlio;
		figlio = 2*figlio;
	}
	lp->heap[padre] = *temp;
	return *item;
}

const char * get_codice_name(Codice codice)
{
	static const char * list_name[CODICE_NUM] = {"BIANCO", "VERDE", "GIALLO", "ROSSO"};
	if (codice >= CODICE_NUM)
		return "";
	return list_name[codice];
}

void stampaListaPazienti(const ListaPazienti * lp)
{
    int i;
	if (lp->heap==NULL)
		return;
	printf("Lista pazienti:\n");
    for (i=1; i<=lp->n; i++)
        stampaPaziente(&lp->heap[i]);
}

void stampaPaziente(const Paziente * p)
{
	if (p==NULL)
		return;
	printf("Nome: %s\n", p->nome);
	printf("Codice: %s\n", get_codice_name(p->codice));
	printf("Ordine: %d\n", p->ordine);
}

