#include <stdio.h>
#include <stdlib.h>

typedef int elemento;

typedef struct nodo
{
	elemento key;
	struct nodo * parent;
	struct nodo * left;
	struct nodo * right;
} Nodo;

Nodo * crea_nodo(elemento key);
Nodo * insert_nodo(Nodo * radice, Nodo * nuovo_nodo);

void visita_nodo(Nodo * r);
void inorder(Nodo * r);
void preorder(Nodo * r);
void postorder(Nodo * r);

int max(int a, int b);
int profondita(Nodo * r);

Nodo * ric_abr_ric(Nodo * radice, elemento chiave);
Nodo * ric_abr_iter(Nodo * radice, elemento chiave);

Nodo * abr_min(Nodo * radice);
Nodo * abr_max(Nodo * radice);

Nodo * abr_succ(Nodo * x);
Nodo * abr_pred(Nodo * x);

Nodo * delete_nodo(Nodo * radice, Nodo * nodo);

void test(Nodo * radice);

#define KEK_N 11
#define KEK2_N 4
int main()
{
	Nodo * radice = NULL;
	Nodo * found = NULL;
	elemento kek[KEK_N] = {45, 34, 20, 14, 27, 38, 60, 55, 48, 58, 72};
	int i;
	for (i=0; i<KEK_N; i++)
		radice = insert_nodo(radice, crea_nodo(kek[i]));
//	radice = insert_nodo(radice, crea_nodo(30));
//	radice = insert_nodo(radice, crea_nodo(25));
//	radice = insert_nodo(radice, crea_nodo(35));
	test(radice);
	radice = (found = ric_abr_ric(radice, 72)) ? delete_nodo(radice, found) : radice;
	test(radice);
	for (i=0; i<KEK_N-1; i++)
		radice = (found = ric_abr_ric(radice, kek[i])) ? delete_nodo(radice, found) : radice;
	test(radice);
	return 0;
}

void test(Nodo * radice)
{
	Nodo * found = NULL;
	elemento kek2[KEK2_N] = {45, 34, 19, 73};
	int i;
	printf("\ninorder:\n");
	inorder(radice);
	printf("\npreorder:\n");
	preorder(radice);
	printf("\npostorder:\n");
	postorder(radice);
	printf("\nprofondita':%d\n", profondita(radice));
	for (i=0; i<KEK2_N; i++)
	{
		printf("ric_abr_ric: %d %s\n", kek2[i], (found = ric_abr_ric(radice, kek2[i])) ? "trovato" : "non trovato");
		printf("ric_abr_iter: %d %s\n", kek2[i], (found = ric_abr_iter(radice, kek2[i])) ? "trovato" : "non trovato");
		// , (found)?found->key:0
		// [res: %d]
	}
	printf("abr_min: %d\n", (found = abr_min(radice)) ? found->key : 0);
	printf("abr_max: %d\n", (found = abr_max(radice)) ? found->key : 0);
	printf("abr_pred of %d: %d\n", 20, (found = ric_abr_ric(radice, 20)) ? (found = abr_pred(found)) ? found->key : 0 : 0);
	printf("abr_succ of %d: %d\n", 20, (found = ric_abr_ric(radice, 20)) ? (found = abr_succ(found)) ? found->key : 0 : 0);
	printf("abr_pred of %d: %d\n", 14, (found = ric_abr_ric(radice, 14)) ? (found = abr_pred(found)) ? found->key : 0 : 0);
	printf("abr_succ of %d: %d\n", 14, (found = ric_abr_ric(radice, 14)) ? (found = abr_succ(found)) ? found->key : 0 : 0);
	printf("abr_pred of %d: %d\n", 27, (found = ric_abr_ric(radice, 27)) ? (found = abr_pred(found)) ? found->key : 0 : 0);
	printf("abr_succ of %d: %d\n", 27, (found = ric_abr_ric(radice, 27)) ? (found = abr_succ(found)) ? found->key : 0 : 0);
}

Nodo * crea_nodo(elemento key)
{
	Nodo * nuovo_nodo = calloc(sizeof(Nodo), 1);
	nuovo_nodo->key = key;
	return nuovo_nodo;
}

Nodo * insert_nodo(Nodo * radice, Nodo * nuovo_nodo)
{
	Nodo * y = NULL;
	Nodo * x = radice;
	while (x != NULL) // L’algoritmo cerca un cammino discendente dalla radice
	{
		y = x; // fino ad una foglia; x segue il cammino, y punta al padre di x
		if (nuovo_nodo->key < x->key)
			x = x->left;
		else if (nuovo_nodo->key > x->key)
			x = x->right;
		else // non presente nelle slide: escludo le key uguali
		{
			free(nuovo_nodo);
			return radice;
		}
	}
	// usciti da questo ciclo y è il puntatore al padre del nuovo nodo
	nuovo_nodo->parent = y;
	if (y == NULL)
		radice = nuovo_nodo;
	else if (nuovo_nodo->key < y->key)
		y->left = nuovo_nodo;
	else
		y->right = nuovo_nodo;
	return radice;
}

void visita_nodo(Nodo * r)
{
	if (r!=NULL)
		printf("%3d ", r->key);
}

void inorder(Nodo * r)
{
	if(r == NULL)
		return;
	inorder(r->left);
	visita_nodo(r);
	inorder(r->right);
}

void preorder(Nodo * r)
{
	if(r == NULL)
		return;
	visita_nodo(r);
	preorder(r->left);
	preorder(r->right);
}

void postorder(Nodo * r)
{
	if(r == NULL)
		return;
	postorder(r->left);
	postorder(r->right);
	visita_nodo(r);
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int profondita(Nodo * r)
{
	if (r == NULL)
		return 0;
	int sx = profondita(r->left);
	int dx = profondita(r->right);
	return 1 + max(sx, dx);
}

Nodo * ric_abr_ric(Nodo * radice, elemento chiave)
{
	if (radice == NULL)
		return NULL;
	else if (chiave == radice->key)
		return radice;
	else if (chiave < radice->key)
		return ric_abr_ric(radice->left, chiave);
	return ric_abr_ric(radice->right, chiave);
}

Nodo * ric_abr_iter(Nodo * radice, elemento chiave)
{
	while (radice != NULL)
	{
		if(chiave == radice->key)
			return radice;
		if(chiave < radice->key)
			radice = radice->left;
		else
			radice = radice->right;
	}
	return NULL;
}

Nodo * abr_min(Nodo * radice)
{
	Nodo * nodo = radice;
	while (nodo!=NULL && nodo->left != NULL)
		nodo = nodo->left;
	return nodo;
}

Nodo * abr_max(Nodo * radice)
{
	Nodo * nodo = radice;
	while (nodo!=NULL && nodo->right != NULL)
		nodo = nodo->right;
	return nodo;
}

Nodo * abr_pred(Nodo * x)
{
	Nodo * y = NULL;
	if (x->left != NULL)
		return abr_max(x->left);
	y = x->parent;
	while (y != NULL && x == y->left)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

Nodo * abr_succ(Nodo * x)
{
	Nodo * y = NULL;
	if (x->right != NULL)
		return abr_min(x->right);
	y = x->parent;
	while (y != NULL && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

Nodo * delete_nodo(Nodo * radice, Nodo * nodo)
{
	Nodo * x = NULL;
	Nodo * y = NULL;
	if (nodo->left == NULL || nodo->right == NULL)
		y = nodo;
	else
		y = abr_succ(nodo);
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;
	if (x != NULL)
		x->parent = y->parent;
	if (y->parent == NULL)
		radice = x;
	else if (y->parent->left == y)
		y->parent->left = x;
	else
		y->parent->right = x;
	if (y != nodo)
		nodo->key = y->key;
	free(y);
	return radice;
}

