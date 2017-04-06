#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIM_CODA 10
#define DIM_STACK 10

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

//prototipi funzioni per la gestione della Coda
//...

//prototipi funzioni per la gestione dello Stack
//...

Node * queue_node_create(int data)
{
	Node * queue_node = NULL;
	queue_node = calloc(sizeof(Node), 1);
	if (queue_node==NULL)
		exit(EXIT_FAILURE);
	queue_node->data = data;
	return queue_node;
}

void queue_print(const Queue * queue)
{
	const Node * queue_node = NULL;
	if (queue==NULL)
		return;
	queue_node = queue->front;
	printf("Node Length: %d\n", queue->cont);
	printf("Node Data:");
	while (queue_node!=NULL)
	{
		printf("%3d", queue_node->data);
		queue_node = queue_node->link;
	}
	printf("\n");
}

void queue_node_print(const Node * queue_node)
{
	if (queue_node==NULL)
		return;
	while (queue_node!=NULL)
	{
		printf("%3d", queue_node->data);
		queue_node = queue_node->link;
	}
}

_Bool queue_isEmpty(const Queue * queue)
{
	if (queue==NULL)
		return true;
	else if (queue->cont==0)
		return true;
	else if (queue->front==NULL && queue->back==NULL)
		return true;
	return false;
}

_Bool queue_isFull(const Queue * queue)
{
	if (queue==NULL)
		return true;
	else if (queue->cont==DIM_CODA)
		return true;
	return false;
}

int queue_getNumElements(const Queue * queue)
{
	if (queue==NULL)
		return 0;
	return queue->cont;
}

int queue_getMaxSize(const Queue * queue)
{
	if (queue==NULL)
		return 0;
	return DIM_CODA;
}

void queue_push(Queue * queue, int elem)
{
	Node * newelem = NULL;
	if (queue==NULL)
		return;
	if (queue_isFull(queue))
	{
		printf("the element %d couldn't be pushed (overflow)\n", elem);
		return;
	}
	newelem = queue_node_create(elem);
	if (queue->front==NULL) //queue_isEmpty(queue))
		queue->front = newelem;
	if (queue->back==NULL)
		queue->back = newelem;
	else
	{
		queue->back->link = newelem;
		queue->back = newelem;
	}
	queue->cont++;
}

int queue_pop(Queue * queue)
{
	Node * oldelem = NULL;
	int oldvalue = -1;
	if (queue==NULL)
		return oldvalue;
	if (queue_isEmpty(queue))
	{
		printf("the element couldn't be popped (underflow)\n");
		return oldvalue;
	}
	oldelem = queue->front;
	oldvalue = oldelem->data;
	queue->cont--;
	if (queue->front->link==NULL)
	{
		queue->front = NULL;
		queue->back = NULL;
	}
	else
	{
		queue->front = queue->front->link;
		free(oldelem);
	}
	return oldvalue;
}

Node * stack_node_create(int data)
{
	Node * stack_node = NULL;
	stack_node = calloc(sizeof(Node), 1);
	if (stack_node==NULL)
		exit(EXIT_FAILURE);
	stack_node->data = data;
	return stack_node;
}

void stack_print(const Stack * stack)
{
	const Node * stack_node = NULL;
	if (stack==NULL)
		return;
	stack_node = stack->top;
	printf("Node Length: %d\n", stack->cont);
	printf("Node Data:");
	while (stack_node!=NULL)
	{
		printf("%3d", stack_node->data);
		stack_node = stack_node->link;
	}
	printf("\n");
}

void stack_node_print(const Node * stack_node)
{
	if (stack_node==NULL)
		return;
	while (stack_node!=NULL)
	{
		printf("%3d", stack_node->data);
		stack_node = stack_node->link;
	}
}

_Bool stack_isEmpty(const Stack * stack)
{
	if (stack==NULL)
		return true;
	else if (stack->cont==0)
		return true;
	else if (stack->top==NULL)
		return true;
	return false;
}

_Bool stack_isFull(const Stack * stack)
{
	if (stack==NULL)
		return true;
	else if (stack->cont==DIM_STACK)
		return true;
	return false;
}

int stack_getNumElements(const Stack * stack)
{
	if (stack==NULL)
		return 0;
	return stack->cont;
}

int stack_getMaxSize(const Stack * stack)
{
	if (stack==NULL)
		return 0;
	return DIM_STACK;
}

void stack_push(Stack * stack, int elem)
{
	Node * newelem = NULL;
	if (stack==NULL)
		return;
	if (stack_isFull(stack))
	{
		printf("the element %d couldn't be pushed (overflow)\n", elem);
		return;
	}
	newelem = stack_node_create(elem);
	if (stack->top==NULL) //stack_isEmpty(stack))
		stack->top = newelem;
	else
	{
		newelem->link = stack->top;
		stack->top = newelem;
	}
	stack->cont++;
}

int stack_pop(Stack * stack)
{
	Node * oldelem = NULL;
	int oldvalue = -1;
	if (stack==NULL)
		return oldvalue;
	if (stack_isEmpty(stack))
	{
		printf("the element couldn't be popped (underflow)\n");
		return oldvalue;
	}
	oldelem = stack->top;
	oldvalue = oldelem->data;
	stack->cont--;
	if (stack->top->link==NULL)
		stack->top = NULL;
	else
	{
		stack->top = stack->top->link;
		free(oldelem);
	}
	return oldvalue;
}

int main()
{
	//dichiarazione e inizializzazione della Coda
	Queue queue;
	queue.front = NULL;
	queue.back = NULL;
	queue.cont = 0;

	//dichiarazione e inizializzazione dello Stack
	Stack stack;
	stack.top = NULL;
	stack.cont = 0;

	//istruzioni e chiamate per i test...
	printf("Queue Test\n");

	queue_print(&queue);
	queue_push(&queue, 11);
	queue_push(&queue, 22);
	queue_push(&queue, 33);
	queue_print(&queue);
	queue_push(&queue, 44);
	queue_push(&queue, 55);
	queue_push(&queue, 66);
	queue_print(&queue);
	queue_push(&queue, 77);
	queue_push(&queue, 88);
	queue_push(&queue, 99);
	queue_push(&queue, 00);
	queue_push(&queue, 11); // overflow (safe)
	queue_print(&queue);
	queue_pop(&queue); //11
	queue_pop(&queue); //22
	queue_pop(&queue); //33
	queue_print(&queue);
	queue_pop(&queue); //44
	queue_pop(&queue); //55
	queue_pop(&queue); //66
	queue_print(&queue);
	printf("popped %d\n", queue_pop(&queue)); //77
	queue_pop(&queue); //88
	queue_pop(&queue); //99
	queue_pop(&queue); //00
	printf("popped %d\n", queue_pop(&queue)); //?? // underflow (safe)
	queue_print(&queue);

	printf("Stack Test\n");
	stack_print(&stack);
	stack_push(&stack, 11);
	stack_push(&stack, 22);
	stack_push(&stack, 33);
	stack_print(&stack);
	stack_push(&stack, 44);
	stack_push(&stack, 55);
	stack_push(&stack, 66);
	stack_print(&stack);
	stack_push(&stack, 77);
	stack_push(&stack, 88);
	stack_push(&stack, 99);
	stack_push(&stack, 00);
	stack_push(&stack, 11); // overflow (safe)
	stack_print(&stack);
	stack_pop(&stack); //00
	stack_pop(&stack); //99
	stack_pop(&stack); //88
	stack_print(&stack);
	stack_pop(&stack); //77
	stack_pop(&stack); //66
	stack_pop(&stack); //55
	stack_print(&stack);
	printf("popped %d\n", stack_pop(&stack)); //44
	stack_pop(&stack); //33
	stack_pop(&stack); //22
	stack_pop(&stack); //11
	printf("popped %d\n", stack_pop(&stack)); //?? // underflow (safe)
	stack_print(&stack);

	return 0;
}
