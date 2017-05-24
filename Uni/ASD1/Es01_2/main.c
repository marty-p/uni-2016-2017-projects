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
/*
 * 
 */
#include <time.h>
#define MIN 0
#define MAX 100
#define N 20000
#define N_LIST 6
#define PCT_SORT_NEXT 80
//#define ENABLE_PRINT_ARRAY
#define TEST_ALL_N
#define SCHEMA_N 4

typedef enum{ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE} inputType;

void processAll(int n);
int get_random_number(int min, int max);
void print_array(int * a, int n);
void swap_numbers(int * a, int n);
int * genera_array(int dimensione, inputType tipo_schema);
void selectionSortWithTime(int * A, int n, inputType tipo_schema);
void selectionSortRec(int * A, int n, int start);
int findmin(int * A, int minpos, int start, int dim);
const char * getTipoSchemaName(inputType tipo_schema);

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
    int i;
    inputType schema_list[SCHEMA_N] = {ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE};

    printf("n=%d\n", n);
    for (i=0; i<SCHEMA_N; i++)
    {
        A = genera_array(n, schema_list[i]);
#ifdef ENABLE_PRINT_ARRAY
        print_array(A, n);
#endif
        selectionSortWithTime(A, n, schema_list[i]);
#ifdef ENABLE_PRINT_ARRAY
        print_array(A, n);
#endif
        free(A);
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

void selectionSortWithTime(int * a, int n, inputType tipo_schema)
{
    clock_t start, end;
    double tempo;
    start = clock();
    // <chiamata all’algoritmo di ordinamento>
    selectionSortRec(a, n, 0);
    // <fine chiamata all’algoritmo di ordinamento>
    end = clock();
    tempo = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("TIPO: %s, N: %d, SECS: %f\n", getTipoSchemaName(tipo_schema), n, tempo);
}

void selectionSortRec(int * A, int dimA, int start)
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

