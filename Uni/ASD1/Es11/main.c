#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>
#include <stdbool.h>
#define MIN 0
#define MAX 100
#define PCT_SORT_NEXT 80
//#define ENABLE_PRINT_ARRAY
#define ENABLE_INPUT_MODE
#define ENABLE_QUICKINSERTION_INPUT

#define TAB "\t"
#define LN "\n"

typedef int elem;
typedef elem * array;

#define SCHEMA_N 4
typedef enum {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE} inputType;
inputType schema_list[SCHEMA_N] = {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE};

#define N_LIST 6
int nList[N_LIST] = {100, 1000, 10000, 100000, 200000, 500000};

#define ALG_N 3
typedef void (*algFunc)(array a, int n, inputType tipo_schema);
typedef enum {INSERTSORT, QUICKSORT, QUICKINSERTSORT} algType;
void insertSortWithTime(array a, int n, inputType tipo_schema);
void quickSortWithTime(array a, int n, inputType tipo_schema);
void quickinsertSortWithTime(array a, int n, inputType tipo_schema);
algFunc algList[ALG_N] = {insertSortWithTime, quickSortWithTime, quickinsertSortWithTime};

// TYPES
const char * get_schema_name(inputType tipo_schema);
const char * get_alg_name(algType tipo_alg);
const char * get_n_name(int n);

int get_schema_input();
int get_alg_input();
int get_n_input();

// MAIN
void processAll();
int get_random_number(int min, int max);
void print_array(array a, int n);
void swap_numbers(array a, int n);
array genera_array(int dimensione, inputType tipo_schema);

void insertionSort(array lista, int dim);
void quickSort(array lista, int u, int v);
void quickinsertionSort(array lista, int u, int v, int M);

int perno(array lista, int primo, int ultimo);
void swap(array a, array b);
int findmin(array A, int minpos, int start, int dim);
const char * getTipoSchemaName(inputType tipo_schema);
_Bool check_sort(array A, int n);

int main(int argc, char** argv)
{
	clock_t start;
	srand(time(NULL));

	start = clock();
	// <chiamata all'algoritmo di ordinamento>
	processAll();
	// <fine chiamata all'algoritmo di ordinamento>
	printf("Processed everything in %.4fs seconds\n", ((double)(clock()-start))/CLOCKS_PER_SEC);
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
	static const char * alg_name[ALG_N] = {"INSERTSORT", "QUICKSORT", "QUICKINSERTSORT"};
	if (tipo_alg >= ALG_N)
		return "";
	return alg_name[tipo_alg];
}

const char * get_n_name(int n)
{
	static const char * n_name[N_LIST] = {"100", "1000", "10000", "100000", "200000", "500000"};
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

void insertSortWithTime(array a, int n, inputType tipo_schema)
{
	clock_t start, end;
	double tempo;
	start = clock();
	// <chiamata all’algoritmo di ordinamento>
	insertionSort(a, n);
	// <fine chiamata all’algoritmo di ordinamento>
	end = clock();
	tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("INSERTION_SORT TIPO: %s, N: %d, SECS: %f\n", getTipoSchemaName(tipo_schema), n, tempo);
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
		do {i = i+1;} while (lista[i] <= pivot && i <= ultimo);
		do {j = j-1;} while (lista[j] > pivot && j >= primo);
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

void quickinsertSortWithTime(array a, int n, inputType tipo_schema)
{
	clock_t start, end;
	double tempo;
	int M = 66;
#ifdef ENABLE_QUICKINSERTION_INPUT
	do
	{
		printf("numero fra %d e %d:\n", MIN, MAX);
		scanf("%d", &M);
	} while (M < MIN || M > MAX);
#endif
	start = clock();
	// <chiamata all’algoritmo di ordinamento>
	quickinsertionSort(a, 0, n-1, M);
	// <fine chiamata all’algoritmo di ordinamento>
	end = clock();
	tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("QUICKINSERTION_SORT TIPO: %s, N: %d, SECS: %f\n", getTipoSchemaName(tipo_schema), n, tempo);
}

void quickinsertionSort(array lista, int u, int v, int M)
{
	int q;
	if (u == v) return;
	if (v-u<=M)
		insertionSort(lista+u, v-u+1);
	else
	{
		q = perno(lista, u, v);
		if (u < q) quickinsertionSort(lista, u, q-1, M);
		if (q < v) quickinsertionSort(lista, q+1, v, M);
	}
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

