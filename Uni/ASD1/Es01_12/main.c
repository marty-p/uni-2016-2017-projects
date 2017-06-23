/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: Studente
 *
 * Created on 8 marzo 2017, 15.00
 */

#include <stdio.h>
#include <stdlib.h>

/*
 Implementare il Selection Sort nella sua versione iterativa.
• Dichiarare un array di N elementi seguendo le seguenti direttive:
1. Popolare l’array con elementi ordinati (1, 2, 3, 4, 5…);
2. Con elementi inversamente ordinati (…5, 4, 3, 2, 1);
3. Con elementi parzialmente ordinati (1, 2, 3, 4, 5, 43, 7, 123, 12, 0, 97…)
4. Con elementi random (… 79, 43, 99, 1, 67…)
• Testare l’algoritmo con N = {100, 1.000, 10.000, 100.000, 200.000 e 500.000}
• Misurare i tempi di esecuzione per ogni dimensione N e per ogni tipologia di
array indicata.
 */
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MIN 0
#define MAX 100
#define N 20000
#define PCT_SORT_NEXT 80
//#define ENABLE_PRINT_ARRAY
#define ENABLE_INPUT_MODE

#define TAB "\t"
#define LN "\n"

typedef int elem;
typedef elem * array;

#define SCHEMA_N 4
typedef enum {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE} inputType;
inputType schema_list[SCHEMA_N] = {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE};

#define N_LIST 6
int nList[N_LIST] = {100, 1000, 10000, 100000, 200000, 500000};

#define ALG_N 2
typedef void (*algFunc)(array a, int n, inputType tipo_schema);
void selectionSortWithTime(array A, int n, inputType tipo_schema);
void selectionSortRecWithTime(array A, int n, inputType tipo_schema);
typedef enum {SELECTSORT_ITER, SELECTSORT_REC} algType;
algFunc algList[ALG_N] = {selectionSortWithTime, selectionSortRecWithTime};

void processAll();
int get_random_number(int min, int max);
void print_array(array a, int n);
void swap_numbers(array a, int n);
array genera_array(int dimensione, inputType tipo_schema);
void selectionSort(array a, int n);
void selectionSortRec(array A, int n, int start);
int findmin(array A, int minpos, int start, int dim);
_Bool check_sort(array A, int n);

const char * get_schema_name(inputType tipo_schema)
{
	static const char * schema_name[SCHEMA_N] = {"ORDINATO", "QUASI_ORDINATO", "INV_ORDINATO", "CASUALE"};
	if (tipo_schema >= SCHEMA_N)
		return "";
	return schema_name[tipo_schema];
}

const char * get_alg_name(algType tipo_alg)
{
	static const char * alg_name[ALG_N] = {"SELECTSORT_ITER", "SELECT_SORT_REC"};
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
    printf("TIPO: %s, N: %d, SECS: %f\n", get_schema_name(tipo_schema), n, tempo);
}

void selectionSortRecWithTime(array a, int n, inputType tipo_schema)
{
    clock_t start, end;
    double tempo;
    start = clock();
    // <chiamata all’algoritmo di ordinamento>
    selectionSortRec(a, n, 0);
    // <fine chiamata all’algoritmo di ordinamento>
    end = clock();
    tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("TIPO: %s, N: %d, SECS: %f\n", get_schema_name(tipo_schema), n, tempo);
}

void selectionSort(array a, int n)
{
    int i, j, min, tmp_min;
    for (i = 0; i < n-1; i++)
    {
        min = i;
        for (j = i+1; j < n; j++)
        {
            if (a[j] < a[min])
                min = j;
        }
        tmp_min = a[min];
        a[min] = a[i];
        a[i] = tmp_min;
    }
}

void selectionSortRec(array A, int dimA, int start)
{
    int tmp_min, minIndex;
    if (start >= dimA-1)
        return;
    minIndex = findmin(A, start, start, dimA);

    tmp_min = A[minIndex];
    A[minIndex] = A[start];
    A[start] = tmp_min;

    selectionSortRec(A, dimA, start+1);
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

