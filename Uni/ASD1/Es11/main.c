#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <stdbool.h>
#define MIN 0
#define MAX 100
#define N 100
//#define N 20000
#define N_LIST 6
#define PCT_SORT_NEXT 80
//#define ENABLE_PRINT_ARRAY
//#define TEST_ALL_N
#define SCHEMA_N 4
//#define ENABLE_QUICKINSERTION_INPUT

typedef enum {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE} inputType;

void processAll(int n);
int get_random_number(int min, int max);
void print_array(int * a, int n);
void swap_numbers(int * a, int n);
int * genera_array(int dimensione, inputType tipo_schema);
void insertionSortWithTime(int * lista, int dim, inputType tipo_schema);
void insertionSort(int * lista, int dim);
void quickSortWithTime(int * a, int n, inputType tipo_schema);
void quickSort(int * lista, int u, int v);
void quickinsertionSortWithTime(int * a, int n, inputType tipo_schema);
void quickinsertionSort(int * lista, int u, int v, int M);
int perno(int * lista, int primo, int ultimo);
void swap(int * a, int * b);
int findmin(int * A, int minpos, int start, int dim);
const char * getTipoSchemaName(inputType tipo_schema);
_Bool check_sort(int * A, int n);

int main(int argc, char** argv)
{
#ifndef TEST_ALL_N
	int n = N;
#else
	int i;
	int nList[N_LIST] = {100, 1000, 10000, 100000, 200000, 500000};
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

void print_array(int * a, int n)
{
	int i;
	for (i=0; i<n; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void processAll(int n)
{
	int * A = NULL;
	int * B = NULL;
	int * C = NULL;
	int i;
	inputType schema_list[SCHEMA_N] = {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE};

	printf("n=%d\n", n);
	for (i=0; i<SCHEMA_N; i++)
	{
		A = genera_array(n, schema_list[i]);
		B = genera_array(n, schema_list[i]);
		C = genera_array(n, schema_list[i]);
#ifdef ENABLE_PRINT_ARRAY
		puts("Print A BEGIN:");
		print_array(A, n);
		puts("Print B BEGIN:");
		print_array(B, n);
		puts("Print C BEGIN:");
		print_array(C, n);
#endif
		insertionSortWithTime(A, n, schema_list[i]);
		quickSortWithTime(B, n, schema_list[i]);
		quickinsertionSortWithTime(C, n, schema_list[i]);
#ifdef ENABLE_PRINT_ARRAY
		puts("Print A END:");
		print_array(A, n);
		puts("Print B END:");
		print_array(B, n);
		puts("Print C END:");
		print_array(C, n);
#endif
		if (check_sort(A, n)==false)
			puts("A wrong sort");
		if (check_sort(B, n)==false)
			puts("B wrong sort");
		if (check_sort(C, n)==false)
			puts("C wrong sort");
		free(A);
		free(B);
		free(C);
	}
}

int * genera_array(int dimensione, inputType tipo_schema)
{
	int i;
	int prev_n = 0;
	int * tmp_a = calloc(dimensione, sizeof(int));
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

void insertionSortWithTime(int * a, int n, inputType tipo_schema)
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

void insertionSort(int * lista, int dim)
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

void quickSortWithTime(int * a, int n, inputType tipo_schema)
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

void quickSort(int * lista, int u, int v)
{
	int q;
	if (u == v) return;
	q = perno(lista, u, v);
	if (u < q) quickSort(lista, u, q-1);
	if (q < v) quickSort(lista, q+1, v);
}

int perno(int * lista, int primo, int ultimo)
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

void swap(int * a, int * b)
{
	int c;
	if (a==NULL || b==NULL)
		return;
	c = *a;
	*a = *b;
	*b = c;
}

void quickinsertionSortWithTime(int * a, int n, inputType tipo_schema)
{
	clock_t start, end;
	double tempo;
	int M = 66;
#ifdef ENABLE_QUICKINSERTION_INPUT
	printf("numero fra %d e %d:\n", MIN, MAX);
	scanf("%d", &M);
#endif
	start = clock();
	// <chiamata all’algoritmo di ordinamento>
	quickinsertionSort(a, 0, n-1, M);
	// <fine chiamata all’algoritmo di ordinamento>
	end = clock();
	tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("QUICKINSERTION_SORT TIPO: %s, N: %d, SECS: %f\n", getTipoSchemaName(tipo_schema), n, tempo);
}

void quickinsertionSort(int * lista, int u, int v, int M)
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

int findmin(int * A, int minpos, int start, int dim)
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

_Bool check_sort(int * A, int n)
{
	int i;
	_Bool isSorted = true;
	for (i=1; i<n && isSorted==true; i++)
		if (A[i-1]>A[i])
			isSorted = false;
	return isSorted;
}

