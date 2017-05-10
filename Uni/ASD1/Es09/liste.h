#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
	int data;
	struct node* link;
} Node;

typedef struct
{
	Node* front;
	Node* back;
	int cont;
} Queue;

typedef struct
{
	Node* top;
	int cont;
} Stack;

Node * insert_node_testa(Node * node, int data);
Node * insert_node_coda(Node * node, int data);

//prototipi funzioni per la gestione della Coda
//...

//prototipi funzioni per la gestione dello Stack
//...

Node * queue_node_create(int data);

void queue_print(const Queue * queue);
void queue_node_print(const Node * queue_node);
_Bool queue_isEmpty(const Queue * queue);
_Bool queue_isFull(const Queue * queue);
int queue_getNumElements(const Queue * queue);
int queue_getMaxSize(const Queue * queue);
void queue_push(Queue * queue, int elem);
int queue_pop(Queue * queue);
Node * stack_node_create(int data);
void stack_print(const Stack * stack);
void stack_node_print(const Node * stack_node);
_Bool stack_isEmpty(const Stack * stack);
_Bool stack_isFull(const Stack * stack);
int stack_getNumElements(const Stack * stack);
int stack_getMaxSize(const Stack * stack);
void stack_push(Stack * stack, int elem);
int stack_pop(Stack * stack);
