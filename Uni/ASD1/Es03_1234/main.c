#include <stdio.h>
#include <stdlib.h>

// #define ENABLE_INPUT_MODE

#define NUMC 15
#define NUMR 10

int numUsedIntegerClassic;
int numUsedIntegerSparse;

void fill_classic_matrix(int matrix[][NUMC], int numr, int numc);
void print_classic_matrix(int matrix[][NUMC], int numr, int numc);
void search_element_in_classic_matrix(int matrix[][NUMC], int numr, int numc, int numric);

typedef struct { int riga, col, valore; } MatriceSparsaT;

MatriceSparsaT * crea_matrice_sparsa(int numr, int numc, int matrix[][numc]);
MatriceSparsaT * crea_matrice_sparsa_input(void);
void print_sparse_matrix(const MatriceSparsaT * matrice_sparsa);
void print_sparse_matrix_as_classic(const MatriceSparsaT * matrice_sparsa);
void search_element_in_sparse_matrix(const MatriceSparsaT * matrice_sparsa, int numric);
void trasp_rapida(const MatriceSparsaT * a, MatriceSparsaT * b);

void input_mode();
void default_mode();

int matrix[NUMR][NUMC] = {{0}};
// int numric = 71;     // assegnare a num il numero da cercare.
MatriceSparsaT * matrice_sparsa = NULL;
MatriceSparsaT * matrice_sparsa_trasposta = NULL;

int main()
{
#ifdef ENABLE_INPUT_MODE
	input_mode();
#else
	default_mode();
#endif

    return 0;
}

void input_mode()
{
}

void default_mode()
{
    // INIZIO TEST MATRICE CLASSICA
    fill_classic_matrix(matrix, NUMR, NUMC);
    printf("\n");
    print_classic_matrix(matrix, NUMR, NUMC);
    // search_element_in_classic_matrix(matrix, NUMR, NUMC, numric);
    search_element_in_classic_matrix(matrix, NUMR, NUMC, 71);
    search_element_in_classic_matrix(matrix, NUMR, NUMC, 99);
    search_element_in_classic_matrix(matrix, NUMR, NUMC, 100);
    // FINE TEST MATRICE CLASSICA

    // INIZIO TEST MATRICE SPARSA
    // Implementare:
        // - creazione matrice sparsa, chiedendo le triple in input (inserite gli stessi valori della matrice classica, vedi slide)
	matrice_sparsa = crea_matrice_sparsa(NUMR, NUMC, matrix);
	//matrice_sparsa = crea_matrice_sparsa_input();
        // - stampa matrice sparsa
	print_sparse_matrix_as_classic(matrice_sparsa);
	print_sparse_matrix(matrice_sparsa);
        // - ricerca di un elemento all'interno della matrice sparsa
	// search_element_in_sparse_matrix(matrice_sparsa, numric);
	search_element_in_sparse_matrix(matrice_sparsa, 71);
	search_element_in_sparse_matrix(matrice_sparsa, 99);
	search_element_in_sparse_matrix(matrice_sparsa, 100);
        // - trasposizione rapida della matrice sparsa.
	matrice_sparsa_trasposta = calloc(matrice_sparsa->valore+1, sizeof(MatriceSparsaT));
	trasp_rapida(matrice_sparsa, matrice_sparsa_trasposta);
	print_sparse_matrix(matrice_sparsa_trasposta);
	print_sparse_matrix_as_classic(matrice_sparsa_trasposta);
    // FINE TEST MATRICE SPARSA
}

void trasp_rapida(const MatriceSparsaT * a, MatriceSparsaT * b)
{
	int * termini_riga = NULL;
	int * pos_iniziale = NULL;
	int i, num_col, num_val, cur_pos;
	num_col = a[0].col;
	num_val = a[0].valore;
	b[0].riga = num_col;
	b[0].col = a[0].riga;
	b[0].valore = num_val;

	termini_riga = calloc(num_col, sizeof(int));
	pos_iniziale = calloc(num_col, sizeof(int));
	if (termini_riga==NULL || pos_iniziale==NULL)
		exit(EXIT_FAILURE);

	if (num_val > 0)
	{
		// creazione termini_riga
		for (i = 0; i<=num_col-1; i++)
			termini_riga[i] = 0;

		for (i = 1; i<=num_val; i++)
			termini_riga[a[i].col] = termini_riga[a[i].col] + 1;

		//creazione pos_iniziale
		pos_iniziale[0] = 1;
		for (i = 1; i<=num_col-1; i++)
			pos_iniziale[i] = pos_iniziale[i-1] + termini_riga[i-1];

		//trasposizione
		for (i = 1; i<=num_val; i++)
		{
			cur_pos = pos_iniziale[a[i].col];
			pos_iniziale[a[i].col] = pos_iniziale[a[i].col] + 1;
			b[cur_pos].riga = a[i].col;
			b[cur_pos].col = a[i].riga;
			b[cur_pos].valore = a[i].valore;
		}
	}
	printf("termini_riga: ");
	for (i=0; i<num_col; i++)
		printf("%d ", termini_riga[i]);
	printf("\n");
	printf("pos_iniziale: ");
	for (i=0; i<num_col; i++)
		printf("%d ", pos_iniziale[i]);
	printf("\n");
}

void fill_classic_matrix(int matrix[][NUMC], int numr, int numc)
{
    matrix[1][0] = 71;
    matrix[2][14] = 99;
    matrix[3][11] = 53;
    matrix[4][7] = 95;
    matrix[6][14] = 39;
    matrix[8][1] = 27;
    matrix[9][14] = 14;
    // matrix[0][0] = 11;
    // matrix[1][1] = 22;
    // matrix[2][6] = 33;
    // matrix[3][3] = 44;
    // matrix[4][14] = 55;
    // matrix[6][12] = 66;
    // matrix[7][7] = 77;
    // matrix[8][10] = 88;
    // matrix[9][11] = 99;
}

void print_classic_matrix(int matrix[][NUMC], int numr, int numc)
{
    int i, j = 0;
    for(i=0; i<numr; i++)
    {
        for(j=0; j<numc; j++)
        {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }

}

void search_element_in_classic_matrix(int matrix[][NUMC], int numr, int numc, int numric)
{
    int i, j = 0;
    for(i=0; i<numr; i++)
    {
        for(j=0; j<numc; j++)
        {
			numUsedIntegerClassic++;
            if(matrix[i][j] == numric)
            {
                printf("Elemento %d trovato in posizione (%d, %d).\n", numric, i, j);
                return;
            }
        }
    }
    printf("Elemento non trovato.\n");
}

void search_element_in_sparse_matrix(const MatriceSparsaT * matrice_sparsa, int numric)
{
	int i;
	if (matrice_sparsa==NULL)
		return;
	for (i=1; i<=matrice_sparsa[0].valore; i++)
	{
		if (numric==matrice_sparsa[i].valore)
		{
			printf("Elemento %d trovato in posizione (%d, %d).\n", numric, matrice_sparsa[i].riga, matrice_sparsa[i].col);
			return;
		}
	}

    printf("Elemento non trovato.\n");
}

void print_sparse_matrix(const MatriceSparsaT * matrice_sparsa)
{
	int i;
	if (matrice_sparsa==NULL)
		return;
	// for (i=1; i<=matrice_sparsa[0].valore; i++)
	for (i=0; i<=matrice_sparsa[0].valore; i++)
		printf("%3d %3d %3d\n", matrice_sparsa[i].riga, matrice_sparsa[i].col, matrice_sparsa[i].valore);
}

void print_sparse_matrix_as_classic(const MatriceSparsaT * matrice_sparsa)
{
	int i, j, c;
	if (matrice_sparsa==NULL)
		return;
	c = 1;
    for (i=0; i<matrice_sparsa[0].riga; i++)
    {
        for (j=0; j<matrice_sparsa[0].col; j++)
        {
			if (matrice_sparsa[c].riga==i && matrice_sparsa[c].col==j)
				printf("%3d", matrice_sparsa[c++].valore);
			else
				printf("  0");
        }
        printf("\n");
    }
}

MatriceSparsaT * crea_matrice_sparsa(int numr, int numc, int matrix[][numc])
{
	int i, j;
	MatriceSparsaT * matrice_sparsa = NULL;
	MatriceSparsaT indice = {numr, numc, 0};
	int c;
	for (i=0; i<numr; i++)
	{
		for (j=0; j<numc; j++)
		{
			if (matrix[i][j]!=0)
				indice.valore++;
		}
	}
	matrice_sparsa = calloc(indice.valore+1, sizeof(MatriceSparsaT));
	if (matrice_sparsa==NULL)
		exit(EXIT_FAILURE);

	matrice_sparsa[0] = indice;
	for (i=0, c=1; i<numr; i++)
	{
		for (j=0; j<numc; j++)
		{
			if (matrix[i][j]!=0)
			{
				matrice_sparsa[c].riga = i;
				matrice_sparsa[c].col = j;
				matrice_sparsa[c].valore = matrix[i][j];
				c++;
			}
		}
	}
	return matrice_sparsa;
}

MatriceSparsaT * inserisci_matrice_sparsa(MatriceSparsaT * matrice_sparsa, MatriceSparsaT tmp, int maxlen)
{
	int i, j;
	if (matrice_sparsa!=NULL && matrice_sparsa[0].valore < maxlen)
	{
		for (i=1; i<=matrice_sparsa[0].valore; i++)
		{
			if (matrice_sparsa[i].riga >= tmp.riga && matrice_sparsa[i].col >= tmp.col)
				break;
		}
		for (j=matrice_sparsa[0].valore; j>=i; j--)
			matrice_sparsa[j+1] = matrice_sparsa[j];
		matrice_sparsa[i] = tmp;
		matrice_sparsa[0].valore++;
	}
	return matrice_sparsa;
}

MatriceSparsaT * crea_matrice_sparsa_input(void)
{
	int c;
	MatriceSparsaT * matrice_sparsa = NULL;
	MatriceSparsaT indice = {0};
	MatriceSparsaT tmp = {0};

	printf("Quante righe deve avere la matrice?\n");
	scanf("%d", &indice.riga);
	while (getchar()!='\n')
		continue;
	printf("Quante colonne deve avere la matrice?\n");
	scanf("%d", &indice.col);
	while (getchar()!='\n')
		continue;
	printf("Quanti valori non nulli deve avere la matrice?\n");
	scanf("%d", &indice.valore);
	while (getchar()!='\n')
		continue;

	matrice_sparsa = calloc(indice.valore+1, sizeof(MatriceSparsaT));
	if (matrice_sparsa==NULL)
		exit(EXIT_FAILURE);

	matrice_sparsa[0] = indice;
	matrice_sparsa[0].valore = 0;

	c=1;
	for (c=1; c<=indice.valore; c++)
	{
		do {
			printf("Inserisci la riga del #%d valore da inserire\n", c);
			scanf("%d", &tmp.riga);
			while (getchar()!='\n')
				continue;

			printf("Inserisci la colonna del #%d valore da inserire\n", c);
			scanf("%d", &tmp.col);
			while (getchar()!='\n')
				continue;

			printf("Inserisci il #%d valore da inserire\n", c);
			scanf("%d", &tmp.valore);
			while (getchar()!='\n')
				continue;
		}
		while (tmp.riga >= indice.riga || tmp.col >= indice.col // skippa out of range
				|| tmp.riga < 0 || tmp.col < 0
				|| tmp.valore==0 // skippa valori 0
				//|| (c>1 && matrice_sparsa[c-1].riga > tmp.riga && matrice_sparsa[c-1].col >= tmp.col) // skippa valori non ordinati
		);
		matrice_sparsa = inserisci_matrice_sparsa(matrice_sparsa, tmp, indice.valore);
		//matrice_sparsa[c] = tmp;
		//matrice_sparsa[0].valore++;
	}
	return matrice_sparsa;
}

