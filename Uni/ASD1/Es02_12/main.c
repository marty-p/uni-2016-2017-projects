#include "load.h"

/*Utilizzare la macro DIM per decidere quale array caricare.
 * I valori possibili sono:
 * - 10
 * - 50
 * - 100
 * - 1000
 * - 10000
 * - 100000
 * - 500000
 * Qualsiasi altro valore non carichera' nessun file.
 * Viene caricato un array di dimensione DIM, gia' ordinato e senza duplicati.
 */
//#define ENABLE_PRINT_ARRAY
#define ENABLE_INPUT_MODE

#define COMBS 2
#define DIM 50
#define NUMS 10

#define TAB "\t"
#define LN "\n"

typedef int elem;
typedef elem * array;

#define N_LIST 7
int nList[N_LIST] = {10, 50, 100, 1000, 10000, 100000, 500000};

/*
 * Dichiarare qui i prototipi delle funzioni necessarie
 */
void printArray(int array[], int dim); //stampa un array di dim elementi



/* Utilizzare le seguenti variabili globali come segue:
 * - contI per contare il numero di passi necessari per trovare l'elemento cercato con la ricerca binaria iterativa
 * - contR per contare il numero di passi necessari per trovare l'elemento cercato con la ricerca binaria ricorsiva
 * - contB per contare il numero di passi necessari per trovare l'elemento cercato con la ricerca banale
 */
int contI = 0, contR = 0, contB = 0;
void processAll(int n, int numric);
int ricercaSemplice(int array[], int dim, int num);
int ricercaBanale(int array[], int dim, int num);
void ricercaBanaleBench(int array[], int dim, int num);
int ricercaBinariaInterattiva(int A[], int dim, int numric);
void ricercaBinariaInterattivaBench(int A[], int dim, int numric);
int ricercaBinariaRicorsiva(int A[], int primo, int ultimo, int numric);
void ricercaBinariaRicorsivaBench(int A[], int dim, int numric);

const char * get_n_name(int n)
{
	static const char * n_name[N_LIST] = {"10", "50", "100", "1000", "10000", "100000", "500000"};
	if (n >= N_LIST)
		return "";
	return n_name[n];
}

int get_n_input()
{
	int i;
	do
	{
		printf("N Input:\n");
		for (i=0; i<N_LIST; i++)
			printf("%d: %s\n", i, get_n_name(i));
		scanf("%d", &i);
		getchar();
	}
	while (i<0 || i>=N_LIST);
	return i;
}

int get_ric_input()
{
	int i;
	printf("NumRic:\n");
	scanf("%d", &i);
	getchar();
	return i;
}

int main()
{
#ifdef ENABLE_INPUT_MODE
	int numric = NUMS; //numero da cercare
	int dim = DIM; //numero da cercare
#else
	int i;
	int nNums[N_LIST][COMBS] = {
		{18, 19}, //10
		{10, 11}, //50
		{34, 35}, //100
		{54, 55}, //1000
		{6, 7}, //10000
		{9, 10}, //100000
		{1, 2}, //500000
	};
#endif

	/* Caricamento dell'array da file in base alla dimensione DIM inserita.
	 * ATTENZIONE: questa funzione e' gia' implementata nei filen load.h e load.c
	 * Non la dovete reimplementare voi.
	 */
#ifdef ENABLE_INPUT_MODE
	dim = nList[get_n_input()];
	numric = get_ric_input();
	processAll(dim, numric);
	processAll(dim, numric+1);
#else
	for (i=0; i<N_LIST; i++)
	{
		processAll(nList[i], nNums[i][0]); // found
		processAll(nList[i], nNums[i][1]); // not found
	}
#endif
	/* Inserire qui di seguito le chiamate ai vari algoritmi di ricerca e calcolare per ognuno:
	 * - il tempo necessario per trovare l'elemento ricercato (se questo e' presente)
	 * - il numero di passi effettuati dall'algoritmo
	 */


	return 0;
}

void printArray(int array[], int dim)
{
	int i;

	for(i = 0; i < dim; i++)
		printf("%d ", array[i]);

	printf("\n");
}

void processAll(int n, int numric)
{
	int *array = NULL;
	array = loadFromFile(n);
	ricercaBanaleBench(array, n, numric);
	ricercaBinariaInterattivaBench(array, n, numric);
	ricercaBinariaRicorsivaBench(array, n, numric);
#ifdef ENABLE_PRINT_ARRAY
	printArray(array, n);
#endif
}

int ricercaBinariaInterattiva(int A[], int dim, int numric)
{
	int primo = 0;
	int ultimo = dim - 1;
	int mezzo;
	contI=0;
	while (primo <= ultimo)
	{
		contI++;
		mezzo = (primo + ultimo)/2;
		if (numric < A[mezzo])
			ultimo = mezzo-1;
		else if (numric == A[mezzo])
			return mezzo;
		else
		   primo = mezzo+1;
	}
	return -1;
}

void ricercaBinariaInterattivaBench(int A[], int dim, int numric)
{
	int res;
	clock_t start, end;
	double tempo;
	start = clock();
	// <chiamata all’algoritmo>
	res = ricercaBinariaInterattiva(A, dim, numric);
	// <fine chiamata all’algoritmo>
	end = clock();
	tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("[BinariaI] NUM: %d, RES=%d, COUNT: %d, N: %d, SECS: %f\n", numric, res, contI, dim, tempo);
}

int ricercaSemplice(int array[], int dim, int num)
{
	int i;
	contB=0;
	for (i=0; i<dim; i++)
	{
		contB++;
		if (array[i]==num)
			return i;
	}
	return -1;
}

int ricercaBanale(int array[], int dim, int num)
{
	int pos = 0;
	contB=0;
	while (pos < dim && array[pos] <= num)
	{
		contB++;
		if (num == array[pos])
			return pos;
		else
			pos++;
	}
	return -1;
}

void ricercaBanaleBench(int array[], int dim, int num)
{
	int res;
	clock_t start, end;
	double tempo;
	start = clock();
	// <chiamata all’algoritmo>
	res = ricercaBanale(array, dim, num);
	// <fine chiamata all’algoritmo>
	end = clock();
	tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("[Banale] NUM: %d, RES=%d, COUNT: %d, N: %d, SECS: %f\n", num, res, contB, dim, tempo);
}

int ricercaBinariaRicorsiva(int A[], int primo, int ultimo, int numric)
{
	int mezzo;
	if (primo > ultimo)
		return -1;
	contR++;
	mezzo = (primo + ultimo)/2;
	if (A[mezzo] == numric)
		return mezzo;
	else if (A[mezzo] < numric)
		return ricercaBinariaRicorsiva(A, mezzo+1, ultimo, numric);
	else
		return ricercaBinariaRicorsiva(A, primo, mezzo-1, numric);
}

void ricercaBinariaRicorsivaBench(int A[], int dim, int numric)
{
	int res;
	clock_t start, end;
	double tempo;
	start = clock();
	// <chiamata all’algoritmo>
	contR=0;
	res = ricercaBinariaRicorsiva(A, 0, dim-1, numric);
	// <fine chiamata all’algoritmo>
	end = clock();
	tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("[BinarioR] NUM: %d, RES=%d, COUNT: %d, N: %d, SECS: %f\n", numric, res, contR, dim, tempo);
}

