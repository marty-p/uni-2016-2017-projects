#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

#include <stdbool.h>

#define MIN 0
#define MAX 100
#define PCT_SORT_NEXT 80
// #define ENABLE_PRINT_ARRAY
#define ENABLE_INPUT_MODE

#define TAB "\t"
#define LN "\n"

typedef int elem;
typedef elem * array;

typedef unsigned long long ullong;
ullong confronti = 0;
ullong scambi = 0;
double tempo = 0.0;

#define SCHEMA_N 4
typedef enum {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE} inputType;
inputType schema_list[SCHEMA_N] = {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE};

#define N_LIST 7
int nList[N_LIST] = {500, 1000, 2000, 5000, 10000, 20000, 50000};

#define ALG_N 5
typedef void (*algFunc)(array a, int n, inputType tipo_schema);
void selectSortWithTime(array a, int n, inputType tipo_schema);
void insertSortWithTime(array a, int n, inputType tipo_schema);
void quickSortWithTime(array a, int n, inputType tipo_schema);
void mergeSortWithTime(array a, int n, inputType tipo_schema);
void heapSortWithTime(array a, int n, inputType tipo_schema);
typedef enum {SELECTSORT, INSERTSORT, MERGESORT, HEAPSORT, QUICKSORT} algType;
algFunc algList[ALG_N] = {selectSortWithTime, insertSortWithTime, mergeSortWithTime, heapSortWithTime, quickSortWithTime};

typedef struct
{
	ullong confronti;
	ullong scambi;
	double tempo;
} Benchmark;
Benchmark scores[SCHEMA_N][N_LIST][ALG_N] = {};

// TYPES
const char * get_schema_name(inputType tipo_schema);
const char * get_alg_name(algType tipo_alg);
const char * get_n_name(int n);

int get_schema_input();
int get_alg_input();
int get_n_input();

// MAIN
void processAll();
void generaTable();

// GENERAL
int get_random_number(int min, int max);
void print_array(array a, int n);
array genera_array(int dimensione, inputType tipo_schema);
void swap(array a, array b);
int findmin(array A, int minpos, int start, int dim);
_Bool check_sort(array A, int n);

// ALGORITHMS
void selectionSort(array a, int n);

void insertionSort(array lista, int dim);

void quickSort(array lista, int u, int v);
int perno(array lista, int primo, int ultimo);

void merge(array lista, array ordinata, int i, int m, int n);
void mergeSort(array lista, array ordinata, int lower, int upper);

void adatta(array lista, int radice, int n);
void heapSort(array lista, int n);

int main(int argc, char** argv)
{
	clock_t start;
	srand(time(NULL));

	start = clock();
	// <chiamata all'algoritmo di ordinamento>
	processAll();
	// <fine chiamata all'algoritmo di ordinamento>
	printf("Processed everything in %.4fs seconds\n", ((double)(clock()-start))/CLOCKS_PER_SEC);
	generaTable();
	return EXIT_SUCCESS;
}

int get_random_number(int min, int max)
{
	return min + rand() % (max - min +1);
}

void print_array(array a, int n)
{
	int i;
	for (i=0; i<n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

const char * get_schema_name(inputType tipo_schema)
{
	static const char * schema_name[SCHEMA_N] = {"ORDINATO", "QUASI_ORDINATO", "INV_ORDINATO", "CASUALE"};
	if (tipo_schema >= SCHEMA_N)
		return "";
	return schema_name[tipo_schema];
}

const char * get_alg_name(algType tipo_alg)
{
	static const char * alg_name[ALG_N] = {"SELECTSORT", "INSERTSORT", "MERGESORT", "HEAPSORT", "QUICKSORT"};
	if (tipo_alg >= ALG_N)
		return "";
	return alg_name[tipo_alg];
}

const char * get_n_name(int n)
{
	static const char * n_name[N_LIST] = {"500", "1000", "2000", "5000", "10000", "20000", "50000"};
	if (n >= N_LIST)
		return "";
	return n_name[n];
}

int get_schema_input()
{
	int i;
	do
	{
		printf("Schema Input:\n");
		for (i=0; i<SCHEMA_N; i++)
			printf("%d: %s\n", i, get_schema_name(i));
		scanf("%d", &i);
		getchar();
	}
	while (i<0 || i>=SCHEMA_N);
	return i;
}

int get_alg_input()
{
	int i;
	do
	{
		printf("Alg Input:\n");
		for (i=0; i<ALG_N; i++)
			printf("%d: %s\n", i, get_alg_name(i));
		scanf("%d", &i);
		getchar();
	}
	while (i<0 || i>=ALG_N);
	return i;
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

void processAll()
{
	array base = NULL;
	array algs[ALG_N] = {0};
	int i, j, k, n;

	#ifndef ENABLE_INPUT_MODE
	for (k=0; k<N_LIST; k++)
	#else
	k = get_n_input();
	#endif
	{
		#ifndef ENABLE_INPUT_MODE
		for (i=0; i<SCHEMA_N; i++)
		#else
		i = get_schema_input();
		#endif
		{
			#ifndef ENABLE_INPUT_MODE
			puts("------------------------------");
			#endif
			n = nList[k];
			base = genera_array(n, schema_list[i]);

			#ifndef ENABLE_INPUT_MODE
			for (j=0; j<ALG_N; j++)
			#else
			j = get_alg_input();
			#endif
			{
				algs[j] = calloc(n, sizeof(elem));
				memcpy(algs[j], base, n*sizeof(elem));

				#ifdef ENABLE_PRINT_ARRAY
				printf("%s BEGIN:\n", get_alg_name(j));
				print_array(algs[j], n);
				#endif

				algList[j](algs[j], n, schema_list[i]);

				scores[i][k][j].tempo = tempo;
				scores[i][k][j].confronti = confronti;
				scores[i][k][j].scambi = scambi;

				#ifdef ENABLE_PRINT_ARRAY
				printf("%s END:\n", get_alg_name(j));
				print_array(algs[j], n);
				#endif

				if (check_sort(algs[j], n)==false)
					printf("%s wrong sort\n", get_alg_name(j));

				free(algs[j]);
				algs[j] = NULL;
			}
		}
		#ifndef ENABLE_INPUT_MODE
		puts("------------------------------------------------------------");
		#endif
	}
}

void generaTable()
{
	int i, j, k;
	FILE * fp = fopen("output.txt", "w");
	if (fp==NULL)
		return;
	for (i=0; i<SCHEMA_N; i++)
	{
		fprintf(fp, "INSIEME %s"LN, get_schema_name(i));
		for (k=0; k<N_LIST; k++)
		{
			fprintf(fp, "------------------------------"LN);
			fprintf(fp, "%s elementi"LN, get_n_name(k));
			for (j=0; j<ALG_N; j++)
			{
				fprintf(fp, "%llu"TAB"%llu"TAB"%.4fs"LN,
					scores[i][k][j].confronti,
					scores[i][k][j].scambi,
					scores[i][k][j].tempo
				);
			}
		}
		fprintf(fp, "------------------------------------------------------------"LN);
	}
	fclose(fp);
}

array genera_array(int dimensione, inputType tipo_schema)
{
	int i;
	int prev_n = 0;
	array tmp_a = calloc(dimensione, sizeof(int));
	if (tmp_a==NULL)
	{
		printf("memoria insufficiente per %d", dimensione);
		exit(EXIT_FAILURE);
	}

	for (i=0; i<dimensione; i++)
	{
		switch (tipo_schema)
		{
			case ORDINATO:
				tmp_a[i] = i;
				break;
			case QUASI_ORDINATO:
				if (get_random_number(MIN, MAX) <= PCT_SORT_NEXT)
					tmp_a[i] = prev_n + 1;
				else
					tmp_a[i] = get_random_number(MIN, MAX);
				prev_n = tmp_a[i];
				break;
			case INV_ORDINATO:
				tmp_a[i] = dimensione-i-1;
				break;
			case CASUALE:
				tmp_a[i] = get_random_number(MIN, MAX);
				break;
		}
	}
	return tmp_a;
}

void selectSortWithTime(array a, int n, inputType tipo_schema)
{
	clock_t start;
	confronti=0, scambi=0;
	start = clock();
	// <chiamata all'algoritmo di ordinamento>
	selectionSort(a, n);
	// <fine chiamata all'algoritmo di ordinamento>
	tempo = ((double)(clock()-start))/CLOCKS_PER_SEC;
	printf("ALG: %s, SCHEMA: %s, N: %d, CONFRONTI: %llu, SCAMBI: %llu, TEMPO: %.4fs\n", get_alg_name(SELECTSORT), get_schema_name(tipo_schema), n, confronti, scambi, tempo);
}

void insertSortWithTime(array a, int n, inputType tipo_schema)
{
	clock_t start;
	confronti=0, scambi=0;
	start = clock();
	// <chiamata all'algoritmo di ordinamento>
	insertionSort(a, n);
	// <fine chiamata all'algoritmo di ordinamento>
	tempo = ((double)(clock()-start))/CLOCKS_PER_SEC;
	printf("ALG: %s, SCHEMA: %s, N: %d, CONFRONTI: %llu, SCAMBI: %llu, TEMPO: %.4fs\n", get_alg_name(INSERTSORT), get_schema_name(tipo_schema), n, confronti, scambi, tempo);
}

void quickSortWithTime(array a, int n, inputType tipo_schema)
{
	clock_t start;
	confronti=0, scambi=0;
	start = clock();
	// <chiamata all'algoritmo di ordinamento>
	quickSort(a, 0, n-1);
	// <fine chiamata all'algoritmo di ordinamento>
	tempo = ((double)(clock()-start))/CLOCKS_PER_SEC;
	printf("ALG: %s, SCHEMA: %s, N: %d, CONFRONTI: %llu, SCAMBI: %llu, TEMPO: %.4fs\n", get_alg_name(QUICKSORT), get_schema_name(tipo_schema), n, confronti, scambi, tempo);
}

void mergeSortWithTime(array a, int n, inputType tipo_schema)
{
	clock_t start;
	array ordinata;
	confronti=0, scambi=0;
	ordinata = calloc(n, sizeof(elem));
	start = clock();
	// <chiamata all'algoritmo di ordinamento>
	mergeSort(a, ordinata, 0, n-1);
	// <fine chiamata all'algoritmo di ordinamento>
	tempo = ((double)(clock()-start))/CLOCKS_PER_SEC;
	printf("ALG: %s, SCHEMA: %s, N: %d, CONFRONTI: %llu, SCAMBI: %llu, TEMPO: %.4fs\n", get_alg_name(MERGESORT), get_schema_name(tipo_schema), n, confronti, scambi, tempo);
	free(ordinata);
}

void heapSortWithTime(array a, int n, inputType tipo_schema)
{
	clock_t start;
	confronti=0, scambi=0;
	start = clock();
	// <chiamata all'algoritmo di ordinamento>
	heapSort(a-1, n);
	// <fine chiamata all'algoritmo di ordinamento>
	tempo = ((double)(clock()-start))/CLOCKS_PER_SEC;
	printf("ALG: %s, SCHEMA: %s, N: %d, CONFRONTI: %llu, SCAMBI: %llu, TEMPO: %.4fs\n", get_alg_name(HEAPSORT), get_schema_name(tipo_schema), n, confronti, scambi, tempo);
}

void swap(array a, array b)
{
	int c;
	if (a==NULL || b==NULL)
		return;
	c = *a;
	*a = *b;
	*b = c;
}

int findmin(array A, int minpos, int start, int dim)
{
	if (start == dim)
		return minpos;
	if (A[start] < A[minpos])
		minpos = start;
	return findmin(A, minpos, start+1, dim);
}

_Bool check_sort(array A, int n)
{
	int i;
	_Bool isSorted = true;
	for (i=1; i<n && isSorted==true; i++)
		if (A[i-1]>A[i])
			isSorted = false;
	return isSorted;
}

void selectionSort(array a, int n)
{
	int i, j, min;
	for (i = 0; i < n-1; i++)
	{
		min = i;
		for (j = i+1; j < n; j++)
		{
			confronti++;
			if (a[j] < a[min])
				min = j;
		}
		swap(&a[min], &a[i]), scambi++;
	}
}

void insertionSort(array lista, int dim)
{
	int i,j;
	int prossimo;
	for (i = 1; i<=dim-1; i++)
	{
		prossimo = lista[i];
		for (j = i-1; j>=0; j--)
		{
			confronti++;
			if (prossimo < lista[j])
				lista[j+1] = lista[j], scambi++;
			else
				break;
		}
		lista[j+1] = prossimo, scambi++;
	}
}

void quickSort(array lista, int u, int v)
{
	int q;
	if (u == v) return;
	q = perno(lista, u, v);
	if (u < q) quickSort(lista, u, q-1);
	if (q < v) quickSort(lista, q+1, v);
}

int perno(array lista, int primo, int ultimo)
{
	int i,j;
	int pivot;
	i = primo;
	j = ultimo + 1;
	pivot = lista[primo];
	while (i < j)
	{
		do {i = i+1; confronti++;} while (lista[i] <= pivot && i <= ultimo);
		do {j = j-1; confronti++;} while (lista[j] > pivot && j >= primo);
		if (i < j)
			swap(&lista[i], &lista[j]), scambi++;
	}
	swap(&lista[primo], &lista[j]), scambi++;
	return j;
}

void merge(array lista, array ordinata, int i, int m, int n)
{
	int j = m+1; // indice per la seconda lista
	int k = i; // indice per la lista ordinata
	int pos_iniziale = i; //posizione iniziale nella lista
	int t;
	while (i <= m && j <= n)
	{
		confronti++, scambi++;
		if (lista[i] <= lista[j])
		{
			ordinata[k] = lista[i];
			i++, k++;
		}
		else
		{
			ordinata[k] = lista[j];
			j++, k++;
		}
	}
	if (i > m)
	{
		// ordinata[k],..., ordinata[n] = lista[j],..., lista[n]
		for (t = j; t <= n; t++)
			ordinata[k + t - j] = lista[t], scambi++;
	}
	else
	{
		// ordinata[k],..., ordinata[n] = lista[i],..., lista[m]
		for (t = i; t <= m; t++)
			ordinata[k + t - i] = lista[t], scambi++;
	}
	// copia ordinata[pos_iniziale : n] in lista[pos_iniziale : n]
	for (i=pos_iniziale; i<=n; i++)
		lista[i]=ordinata[i]; //no scambi++;
}

void mergeSort(array lista, array ordinata, int lower, int upper)
{
	int medium;
	if (lower >= upper)
		return;
	medium = (lower + upper)/2;
	mergeSort(lista, ordinata, lower, medium);
	mergeSort(lista, ordinata, medium+1, upper);
	merge(lista, ordinata, lower, medium, upper);
}

void adatta(array lista, int radice, int n)
{
	elem temp = lista[radice];
	elem figlio = 2 * radice; // figlio sx
	while (figlio <= n)
	{
		// trova il maggiore tra il figlio sx e figlio dx
		confronti++;
		if (figlio < n && lista[figlio] < lista[figlio+1])
			figlio = figlio + 1;
		// confronta la radice e figlio max
		confronti++;
		if (temp > lista[figlio])
			break; // il padre di figlio sarà la posizione corretta
		else
		{
			lista[figlio/2] = lista[figlio], scambi++; // il figlio si sposta verso il padre
			// ripeti sul sottoalbero selezionato
			figlio = 2 * figlio;
		}
	}
	lista[figlio/2] = temp, scambi++; // copia la radice nella posizione corretta
}

void heapSort(array lista, int n)
{
	int i;
	// Si costruisce lo heap associato all'insieme da ordinare lista
	for (i = n/2; i>=1; i--)
		adatta(lista, i, n);
	for (i = n-1; i>=1; i--)
	{
		//si estrae, di volta in volta, il massimo lista[1] e lo si posiziona in fondo alla sequenza
		swap(&lista[1], &lista[i+1]), scambi++;
		// si opera nuovamente sullo heap ridotto di un elemento
		adatta(lista, 1, i);
	}
}

