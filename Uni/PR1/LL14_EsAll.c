// ### MARTY
// ## no warnings: (clang 3.4.1, clang 3.3, gcc 4.2.1, vs2010)
// # clang -Wall LL14_EsAll.c
// ## tryharding: (clang, gcc will be ok if all the // comments will be removed under -ansi, vs2010 has no -ansi) [ansi == c89 == c90]
// # clang -ansi -Wall -Wno-comment LL14_EsAll.c
// # ./a.out
#include <stdio.h>
#include <stdlib.h>

// [Since C90 From C99 Section 7.20.3.2: If ptr is a null pointer, no action occurs.]
#define _free(ptr) if (ptr != NULL) { free(ptr); ptr = NULL; }
#define _free_node(ptr) if (ptr != NULL) { free_node(ptr); ptr = NULL; }
#define _free_nodes(ptr) if (ptr != NULL) { free_nodes(ptr); ptr = NULL; }
#define _free_nodes_cur(ptr) if (ptr != NULL) { free_nodes_cur(ptr); ptr = NULL; }

typedef struct node_s // same if `node_t`
{
	int number;
	struct node_s * next; // same if `struct node_t`
} node_t;

typedef node_t * LPNODE; // todo refactor
typedef LPNODE * LPNODES; // todo refactor

node_t * create_node(int number);
void free_node(node_t * pNode);
void free_nodes(node_t * pNode);
void free_nodes_cur(node_t * pNode);

/*1. Scrivere una funzione che inserisce un nodo in testa alla lista. Utilizzare la funzione per popolare una
lista di numeri interi positivi inseriti dall'utente. L'acquisizione termina quando il valore inserito è
negativo.*/
void add_nodes_head(node_t ** pNodes, int number);

/*2. Scrivere una funzione che permetta di stampare gli elementi di una lista.*/
void print_nodes(node_t * pNode);
void print_nodes_cur_inv(node_t * pNode);

/*3. Scrivere una funzione che restituisca la dimensione di una lista.*/
int count_nodes(node_t * pNode);

/*4. Scrivere una funzione che effettui la ricerca di un elemento all'interno di una lista.*/
node_t * find_nodes(node_t * pNode, int number);

/*5. Scrivere una funzione che restituisca il number di occorrenze all'interno di una lista di un dato
number.*/
int count_elem_n_nodes(node_t * pNode, int number);

/*6. Scrivere una funzione che permetta l'inserimento di un nodo all'interno di una lista. Il nodo deve
essere inserito nella posizione successiva ad un nodo già presente nella lista e passato come
parametro. */
void add_nodes_tail(node_t ** pNodes, int number);
void add_nodes_after_n(node_t ** pNodes, int number, int before_n);

/*7. Scrivere una funzione che acquisisca dei numeri interi (come es. 1) e si occupi di inserire i valori in
una lista facendo in modo che la lista sia sempre ordinata.*/
node_t * find_nodes_higher_than(node_t * pNode, int number);
void add_nodes_sorted(node_t ** pNodes, int number);

/*8. Scrivere una funzione che elimini un nodo da una lista. Gestire l'eliminazione in testa, in coda e al
centro della lista. */
void remove_nodes_head(node_t ** pNodes);
void remove_nodes_tail(node_t ** pNodes);
void remove_nodes_n(node_t ** pNodes, int n);
node_t * find_nodes_prev(node_t * pNode, int number, node_t ** pNodePrevious);

int main(void)
{
	node_t * nodes = NULL;
	int inputNumber;
	node_t * pNodePrevious = NULL;

	do {
		printf("Insert a positive number:\n");
		scanf("%d", &inputNumber);
		getchar(); // discarding non-number characters otherwise it gets in an infinite loop
		// add_nodes_head(&nodes, inputNumber);
		// add_nodes_tail(&nodes, inputNumber);
		add_nodes_sorted(&nodes, inputNumber);
	} while (inputNumber >= 0);

	// add_nodes_after_n(&nodes, 666, 2);

	// remove_nodes_head(&nodes);
	// remove_nodes_tail(&nodes);
	// remove_nodes_n(&nodes, -1);
	// remove_nodes_n(&nodes, 666);

	print_nodes(nodes);

	print_nodes_cur_inv(nodes);
	printf("\n"); // newline a little too complex to add in the reversed recursing procedure

	printf("count %d\n", count_nodes(nodes));

	printf("count of 1 is %d\n", count_elem_n_nodes(nodes, 1));

	pNodePrevious = find_nodes(nodes, -1);
	if (pNodePrevious != NULL)
		printf("value -1 found\n");
	else
		printf("value -1 not found\n");

	_free_nodes(nodes);
	// _free_nodes_cur(nodes);

	return 0;
}

node_t * create_node(int number)
{
	node_t * tmp = malloc(sizeof(node_t));
	if (tmp == NULL) // not enough memory
		exit(EXIT_FAILURE); // instead of exit(-1) otherwise abort()
	tmp->number = number;
	tmp->next = NULL;
	return tmp;
}

void add_nodes_head(node_t ** pNodes, int number)
{
	node_t * pNodeHead = NULL;
	if ((*pNodes) == NULL)
		(*pNodes) = create_node(number);
	else
	{
		pNodeHead = create_node(number);
		pNodeHead->next = (*pNodes);
		(*pNodes) = pNodeHead;
	}
}

void add_nodes_tail(node_t ** pNodes, int number)
{
	if ((*pNodes) == NULL)
		(*pNodes) = create_node(number);
	else
	{
		while ((*pNodes)->next != NULL)
			pNodes = &(*pNodes)->next;
		(*pNodes)->next = create_node(number);
		pNodes = &(*pNodes)->next;
	}
}

void add_nodes_after_n(node_t ** pNodes, int number, int before_n)
{
	node_t * pNodeFound = find_nodes(*pNodes, before_n);
	node_t * pNodeOldNext = NULL;
	if (pNodeFound != NULL)
	{
		pNodeOldNext = pNodeFound->next;
		pNodeFound->next = create_node(number);
		pNodeFound->next->next = pNodeOldNext;
	}
	else // added in the end if not found
		add_nodes_tail(pNodes, number);
}

void add_nodes_sorted(node_t ** pNodes, int number)
{
	node_t * pNodePrevious = find_nodes_higher_than(*pNodes, number);
	node_t * pNodeOldNext = NULL;
	if (pNodePrevious == NULL)
		add_nodes_head(pNodes, number);
	else
	{
		pNodeOldNext = pNodePrevious->next;
		pNodePrevious->next = create_node(number);
		pNodePrevious->next->next = pNodeOldNext;
	}
}

void remove_nodes_head(node_t ** pNodes)
{
	node_t * pNodeSecond = NULL;
	if ((*pNodes) == NULL)
		return;
	pNodeSecond = (*pNodes)->next;
	_free_node(*pNodes);
	(*pNodes) = pNodeSecond;
}

void remove_nodes_tail(node_t ** pNodes)
{
	node_t * pNodePrevious = (*pNodes);
	if ((*pNodes) == NULL)
		return;
	while ((*pNodes)->next != NULL)
	{
		pNodePrevious = (*pNodes);
		pNodes = &(*pNodes)->next;
	}
	_free_node(*pNodes);
	pNodePrevious->next = NULL;
}

void remove_nodes_n(node_t ** pNodes, int n)
{
	node_t * pNodePrevious = NULL;
	node_t * pNodeFound = find_nodes_prev(*pNodes, n, &pNodePrevious);
	if (pNodeFound != NULL)
	{
		if (pNodePrevious != NULL) // middle or tail
			pNodePrevious->next = pNodeFound->next;
		else // head
			*pNodes = pNodeFound->next;
		_free_node(pNodeFound);
	}
	// else // remove the last if not found
		// remove_nodes_tail(pNodes);
}

void print_nodes(node_t * pNode)
{
	while (pNode != NULL)
	{
		printf("%4d", pNode->number);
		pNode = pNode->next;
	}
	printf("\n");
}

void print_nodes_cur(node_t * pNode)
{
	if (pNode != NULL)
	{
		printf("%4d", pNode->number);
		print_nodes_cur_inv(pNode->next);
	}
	else
		printf("\n");
}

void print_nodes_cur_inv(node_t * pNode)
{
	if (pNode != NULL)
	{
		print_nodes_cur_inv(pNode->next);
		printf("%4d", pNode->number);
	}
}

int count_nodes(node_t * pNode)
{
	int count = 0;
	while (pNode != NULL)
	{
		pNode = pNode->next;
		count++;
	}
	return count;
}

int count_elem_n_nodes(node_t * pNode, int number)
{
	int count = 0;
	while (pNode != NULL)
	{
		if (pNode->number == number)
			count++;
		pNode = pNode->next;
	}
	return count;
}

node_t * find_nodes(node_t * pNode, int number)
{
	node_t * pNodeFound = NULL;
	while (pNode != NULL && pNodeFound == NULL)
	{
		if (pNode->number == number)
			pNodeFound = pNode;
		pNode = pNode->next;
	}
	return pNodeFound;
}

node_t * find_nodes_higher_than(node_t * pNode, int number)
{
	node_t * pNodeFound = NULL;
	node_t * pNodePrevious = NULL;
	while (pNode != NULL && pNodeFound == NULL)
	{
		if (pNode->number > number)
			pNodeFound = pNode;
		else
			pNodePrevious = pNode;
		pNode = pNode->next;
	}
	return pNodePrevious;
}

node_t * find_nodes_prev(node_t * pNode, int number, node_t ** pNodePrevious)
{
	node_t * pNodeFound = NULL;
	*pNodePrevious = NULL;
	while (pNode != NULL && pNodeFound == NULL)
	{
		if (pNode->number == number)
			pNodeFound = pNode;
		else
			*pNodePrevious = pNode;
		pNode = pNode->next;
	}
	return pNodeFound;
}

void free_node(node_t * pNode)
{
	_free(pNode);
}

void free_nodes(node_t * pNode)
{
	node_t * pNodePrevious = NULL;
	while (pNode != NULL)
	{
		pNodePrevious = pNode;
		pNode = pNode->next;
		_free_node(pNodePrevious);
	}
}

void free_nodes_cur(node_t * pNode)
{
	if (pNode == NULL)
		return;
	free_nodes_cur(pNode->next);
	_free_node(pNode);
}

