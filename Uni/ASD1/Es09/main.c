#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"

#define MAX_VERTEX 25
#define QUEUE_SIZE MAX_VERTEX
#define N_NAME 30

/*typedef struct node
{
	struct node* next;
	int vertex_id;
} Node;*/

typedef struct city
{
	char name[N_NAME];
} City;

/*typedef struct
{
	Node* front;
	Node* back;
	int cont;
} Queue;*/

typedef Node* lpNode;

City cities[MAX_VERTEX] = {};
lpNode graph[MAX_VERTEX] = {};
int visited[MAX_VERTEX] = {};

#define DEFAULT_N 11
enum eCities
{
	Cagliari, Zurigo, Lione, Genova, Roma, NewYork, Bilbao, Berlino, Londra, Miami, Tokyo
};

void default_set();

void print_lista_adiacenza();
void visita_rec(int id);
void visita_nodo(const Node * node);
void visita(int id);

void visita_in_profondita(int id);
void visita_in_ampiezza(int id);

int main()
{
	// printf("Lavorate in silenzio!");
	// printf("Non c'e' nulla da consegnare");
	// printf("Visitare un nodo vuol dire stamparne le informazioni");
	default_set();
	printf("lista_adiacenza:\n");
	print_lista_adiacenza();

	printf("visita_in_profondita: (Cagliari)\n");
	memset(visited, 0, sizeof(visited));
	visita_in_profondita(Cagliari);
	printf("\n");

	printf("visita_in_profondita: (Roma)\n");
	memset(visited, 0, sizeof(visited));
	visita_in_profondita(Roma);
	printf("\n");

	printf("visita_in_ampiezza: (Cagliari)\n");
	memset(visited, 0, sizeof(visited));
	visita_in_ampiezza(Cagliari);
	printf("\n");

	printf("visita_in_ampiezza: (Roma)\n");
	memset(visited, 0, sizeof(visited));
	visita_in_ampiezza(Roma);
	printf("\n");

	return 0;
}

void default_set()
{
	const char * city_names[DEFAULT_N] = {"Cagliari", "Zurigo", "Lione", "Genova", "Roma", "New York", "Bilbao", "Berlino", "Londra", "Miami", "Tokyo"};
	int i;
	for (i=0; i<DEFAULT_N; i++)
		strcpy(cities[i].name, city_names[i]);

	// Cagliari -> Zurigo -> Roma
	graph[Cagliari] = insert_node_coda(graph[Cagliari], Zurigo);
	graph[Cagliari] = insert_node_coda(graph[Cagliari], Roma);
	// Zurigo -> Cagliari -> Lione
	graph[Zurigo] = insert_node_coda(graph[Zurigo], Cagliari);
	graph[Zurigo] = insert_node_coda(graph[Zurigo], Lione);
	// Lione -> Zurigo -> Genova
	graph[Lione] = insert_node_coda(graph[Lione], Zurigo);
	graph[Lione] = insert_node_coda(graph[Lione], Genova);
	// Genova
	// Roma -> Cagliari -> Zurigo -> NewYork -> Bilbao
	graph[Roma] = insert_node_coda(graph[Roma], Cagliari);
	graph[Roma] = insert_node_coda(graph[Roma], Zurigo);
	graph[Roma] = insert_node_coda(graph[Roma], NewYork);
	graph[Roma] = insert_node_coda(graph[Roma], Bilbao);
	// NewYork -> Zurigo
	graph[NewYork] = insert_node_coda(graph[NewYork], Zurigo);
	// Bilbao -> Berlino
	graph[Bilbao] = insert_node_coda(graph[Bilbao], Berlino);
	// Berlino
	// Londra -> Miami
	graph[Londra] = insert_node_coda(graph[Londra], Miami);
	// Miami -> Londra -> Tokyo
	graph[Miami] = insert_node_coda(graph[Miami], Londra);
	graph[Miami] = insert_node_coda(graph[Miami], Tokyo);
	// Tokyo
}

void print_lista_adiacenza()
{
	int i;
	for (i=0; i<MAX_VERTEX && cities[i].name[0]!='\0'; i++)
		visita_rec(i);
}

void visita_rec(int id)
{
	lpNode tmp = graph[id];
	visita(id);
	while (tmp!=NULL)
	{
		printf(" -> ");
		visita_nodo(tmp);
		tmp = tmp->link;
	}
	printf("\n");
}

void visita_nodo(const Node * node)
{
	if (node!=NULL)
		visita(node->data);
}

void visita(int id)
{
	printf("%s", cities[id].name);
}

void visita_in_profondita(int id)
{
	visita(id);
	visited[id] = 1;
	const Node * tmp = graph[id];
	int id_next = 0;
	while (tmp != NULL)
	{
		id_next = tmp->data;
		if (visited[id_next]==0)
		{
			printf(", ");
			visita_in_profondita(id_next);
		}
		tmp = tmp->link;
	}
}

void visita_in_ampiezza(int id)
{
	lpNode tmp = NULL;
	int i;
	visita(id);
	visited[id] = 1;
	Queue C = {};
	queue_push(&C, id);
	while (!queue_isEmpty(&C))
	{
		i = queue_pop(&C);
		tmp = graph[i];
		while (tmp != NULL)
		{
			if (visited[tmp->data]==0)
			{
				queue_push(&C, tmp->data);
				printf(", ");
				visita_nodo(tmp);
				visited[tmp->data]=1;
			}
			tmp = tmp->link;
		}
	}
}

