#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>
#include <stdbool.h>
#define MIN 0
#define MAX 100
#define N 100
//#define N 20000
#define PCT_SORT_NEXT 80
#define ENABLE_PRINT_ARRAY
//#define TEST_ALL_N

typedef int elem;
typedef elem * array;

#define SCHEMA_N 4
typedef enum {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE} inputType;
inputType schema_list[SCHEMA_N] = {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE};

#define N_LIST 7
int nList[N_LIST] = {500, 1000, 2000, 5000, 10000, 20000, 50000};

#define ALG_LIST 5
typedef void (*algFunc)(array a, int n, inputType tipo_schema);
void selectionSortWithTime(array a, int n, inputType tipo_schema);
void insertionSortWithTime(array a, int n, inputType tipo_schema);
void quickSortWithTime(array a, int n, inputType tipo_schema);
void mergeSortWithTime(array a, int n, inputType tipo_schema);
void heapSortWithTime(array a, int n, inputType tipo_schema);
algFunc algList[ALG_LIST] = {selectionSortWithTime, insertionSortWithTime, quickSortWithTime, mergeSortWithTime, heapSortWithTime};

typedef struct
{
	int confronti;
	int scambi;
	double tempo;
} Benchmark;

Benchmark score[SCHEMA_N][N_LIST][ALG_LIST] = {};

void processAll(int n);
int get_random_number(int min, int max);
void print_array(array a, int n);
void swap_numbers(array a, int n);
array genera_array(int dimensione, inputType tipo_schema);

void insertionSort(array lista, int dim);
void quickSort(array lista, int u, int v);
int perno(array lista, int primo, int ultimo);
void swap(array a, array b);
int findmin(array A, int minpos, int start, int dim);
const char * getTipoSchemaName(inputType tipo_schema);
_Bool check_sort(array A, int n);

void merge(array lista, array ordinata, int i, int m, int n);
void mergeSort(array lista, array ordinata, int lower, int upper);

void adatta(array lista, int radice, int n);
void heapSort(array lista, int n);

void selectionSort(array a, int n);

int main(int argc, char** argv)
{
#ifndef TEST_ALL_N
	int n = N;
#else
	int i;
#endif
	srand(time(NULL));
#ifndef TEST_ALL_N
	processAll(n);
#else
	for (i=0; i<N_LIST; i++)
		processAll(nList[i]);
#endif
	return (EXIT_SUCCESS);
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

void processAll(int n)
{
	array base = NULL;
	array insertArray = NULL;
	array quickArray = NULL;
	array mergeArray = NULL;
	array heapArray = NULL;
	array selectArray = NULL;
	int i;

	printf("n=%d\n", n);
	for (i=0; i<SCHEMA_N; i++)
	{
		base = genera_array(n, schema_list[i]);

		insertArray = calloc(n, sizeof(elem));
		memcpy(insertArray, base, n*sizeof(elem));

		quickArray = calloc(n, sizeof(elem));
		memcpy(quickArray, base, n*sizeof(elem));

		mergeArray = calloc(n, sizeof(elem));
		memcpy(mergeArray, base, n*sizeof(elem));

		heapArray = calloc(n, sizeof(elem));
		memcpy(heapArray, base, n*sizeof(elem));

		selectArray = calloc(n, sizeof(elem));
		memcpy(selectArray, base, n*sizeof(elem));

#ifdef ENABLE_PRINT_ARRAY
		puts("insertArray BEGIN:");
		print_array(insertArray, n);

		puts("quickArray BEGIN:");
		print_array(quickArray, n);

		puts("mergeArray BEGIN:");
		print_array(mergeArray, n);

		puts("heapArray BEGIN:");
		print_array(heapArray, n);

		puts("selectArray BEGIN:");
		print_array(selectArray, n);
#endif

		insertionSortWithTime(insertArray, n, schema_list[i]);
		quickSortWithTime(quickArray, n, schema_list[i]);
		mergeSortWithTime(mergeArray, n, schema_list[i]);
		heapSortWithTime(heapArray, n, schema_list[i]);
		selectionSortWithTime(selectArray, n, schema_list[i]);

#ifdef ENABLE_PRINT_ARRAY
		puts("insertArray END:");
		print_array(insertArray, n);

		puts("quickArray END:");
		print_array(quickArray, n);

		puts("mergeArray END:");
		print_array(mergeArray, n);

		puts("heapArray END:");
		print_array(heapArray, n);

		puts("selectArray END:");
		print_array(selectArray, n);
#endif

		if (check_sort(insertArray, n)==false)
			puts("insertArray wrong sort");

		if (check_sort(quickArray, n)==false)
			puts("quickArray wrong sort");

		if (check_sort(mergeArray, n)==false)
			puts("mergeArray wrong sort");

		if (check_sort(heapArray, n)==false)
			puts("heapArray wrong sort");

		if (check_sort(selectArray, n)==false)
			puts("selectArray wrong sort");

		free(insertArray);
		insertArray = NULL;

		free(quickArray);
		quickArray = NULL;

		free(mergeArray);
		mergeArray = NULL;

		free(heapArray);
		heapArray = NULL;

		free(selectArray);
		selectArray = NULL;
	}
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

void insertionSortWithTime(array a, int n, inputType tipo_schema)
{
	clock_t start, end;
	double tempo;
	start = clock();
	// <chiamata all’algoritmo di ordinamento>
	insertionSort(a, n);
	// <fine chiamata all’algoritmo di ordinamento>
	end = clock();
	tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("INSERT_SORT TIPO: %s, N: %d, SECS: %f\n", getTipoSchemaName(tipo_schema), n, tempo);
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
			if (prossimo < lista[j])
				lista[j+1] = lista[j];
			else
				break;
		}
		lista[j+1] = prossimo;
	}
}

void quickSortWithTime(array a, int n, inputType tipo_schema)
{
	clock_t start, end;
	double tempo;
	start = clock();
	// <chiamata all’algoritmo di ordinamento>
	quickSort(a, 0, n-1);
	// <fine chiamata all’algoritmo di ordinamento>
	end = clock();
	tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("QUICK_SORT TIPO: %s, N: %d, SECS: %f\n", getTipoSchemaName(tipo_schema), n, tempo);
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
		do {i = i+1;} while (lista[i] <= pivot);
		do {j = j-1;} while (lista[j] > pivot);
		if (i < j)
			swap(&lista[i], &lista[j]);
	}
	swap(&lista[primo], &lista[j]);
	return j;
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

const char * getTipoSchemaName(inputType tipo_schema)
{
	static const char * schema_name[SCHEMA_N] = {"ORDINATO", "QUASI_ORDINATO", "INV_ORDINATO", "CASUALE"};
	if (tipo_schema >= SCHEMA_N)
		return "";
	return schema_name[tipo_schema];
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

void merge(array lista, array ordinata, int i, int m, int n)
{
	int j = m+1; // indice per la seconda lista
	int k = i; // indice per la lista ordinata
	int pos_iniziale = i; //posizione iniziale nella lista
	int t;
	while (i <= m && j <= n)
	{
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
			ordinata[k + t - j] = lista[t];
	}
	else
	{
		// ordinata[k],..., ordinata[n] = lista[i],..., lista[m]
		for (t = i; t <= m; t++)
			ordinata[k + t - i] = lista[t];
	}
	// copia ordinata[pos_iniziale : n] in lista[pos_iniziale : n]
	for (i=pos_iniziale; i<=n; i++)
		lista[i]=ordinata[i];
}

void mergeSort(array lista, array ordinata, int lower, int upper)
{
	if (lower >= upper)
		return;
	int medium = (lower + upper)/2;
	mergeSort(lista, ordinata, lower, medium);
	mergeSort(lista, ordinata, medium+1, upper);
	merge(lista, ordinata, lower, medium, upper);
}

void mergeSortWithTime(array a, int n, inputType tipo_schema)
{
	array ordinata = calloc(n, sizeof(elem));
	clock_t start, end;
	double tempo;
	start = clock();
	// <chiamata all’algoritmo di ordinamento>
	mergeSort(a, ordinata, 0, n-1);
	// <fine chiamata all’algoritmo di ordinamento>
	end = clock();
	tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("MERGE_SORT TIPO: %s, N: %d, SECS: %f\n", getTipoSchemaName(tipo_schema), n, tempo);
	free(ordinata);
}

void adatta(array lista, int radice, int n)
{
	elem temp = lista[radice];
	elem figlio = 2 * radice; // figlio sx
	while (figlio <= n)
	{
		// trova il maggiore tra il figlio sx e figlio dx
		if (figlio < n && lista[figlio] < lista[figlio+1])
			figlio = figlio + 1;
		// confronta la radice e figlio max
		if (temp > lista[figlio])
			break; // il padre di figlio sarà la posizione corretta
		else
		{
			lista[figlio/2] = lista[figlio]; // il figlio si sposta verso il padre
			// ripeti sul sottoalbero selezionato
			figlio = 2 * figlio;
		}
	}
	lista[figlio/2] = temp; // copia la radice nella posizione corretta
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
		swap(&lista[1], &lista[i+1]);
		// si opera nuovamente sullo heap ridotto di un elemento
		adatta(lista, 1, i);
	}
}

void heapSortWithTime(array a, int n, inputType tipo_schema)
{
	array heap = calloc(n+1, sizeof(elem));
//	int i;
//	for (i=0; i<n; i++)
//		heap[i+1]=a[i];
	memcpy(heap+1, a, n*sizeof(elem));
	clock_t start, end;
	double tempo;
	start = clock();
	// <chiamata all’algoritmo di ordinamento>
	heapSort(heap, n);
	// <fine chiamata all’algoritmo di ordinamento>
	end = clock();
	tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("HEAP_SORT TIPO: %s, N: %d, SECS: %f\n", getTipoSchemaName(tipo_schema), n, tempo);
//	for (i=0; i<n; i++)
//		a[i]=heap[i+1];
	memcpy(a, heap+1, n*sizeof(elem));
	free(heap);
}

void selectionSortWithTime(array a, int n, inputType tipo_schema)
{
    clock_t start, end;
    double tempo;
    start = clock();
    // <chiamata all’algoritmo di ordinamento>
    selectionSort(a, n);
    // <fine chiamata all’algoritmo di ordinamento>
    end = clock();
    tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("SELECT_SORT TIPO: %s, N: %d, SECS: %f\n", getTipoSchemaName(tipo_schema), n, tempo);
}

void selectionSort(array a, int n)
{
    int i, j, min;
    for (i = 0; i < n-1; i++)
    {
        min = i;
        for (j = i+1; j < n; j++)
        {
            if (a[j] < a[min])
                min = j;
        }
		swap(&a[min], &a[i]);
    }
}

