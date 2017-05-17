#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLOORS 10
typedef struct car
{
	const char * plate_number;
	struct car * next;
} Car;
typedef Car* lpCar;

//La struttura dati che rappresenta il parcheggio multipiano;
Car * carpark[MAX_FLOORS] = {};

void print_car_list();
void print_car_rec(int id);
void print_cars(const Car * node);
void print_car(const char * plate_number);

int hash_code(const char* plate_number);
void insert_car(const char * plate_number);
lpCar search_car(const char * plate_number);
void delete_car(const char * plate_number);
lpCar delete_car_node(Car * node, const char * plate_number);

Car * insert_car_testa(Car * node, const char* plate_number);
Car * insert_car_coda(Car * node, const char* plate_number);

void default_set();

int main()
{
	// test insert
	default_set();
	print_car_list();
	// test search
	lpCar nodo = search_car("GG677GG");
	if (nodo!=NULL)
		nodo->plate_number = "KEK";
	printf("\n\n\n\n");
	print_car_list();
	// test delete
	delete_car("JJ100JJ");
	printf("\n\n\n\n");
	print_car_list();
	// test multiple delete
	delete_car("JJ000JJ");
	delete_car("CC333CC");
	printf("\n\n\n\n");
	print_car_list();
	return 0;
}

//#define DEFAULT_N 4
#define DEFAULT_N 15
void default_set()
{
	//const char * lista_targhe[DEFAULT_N] = {"PI555TA", "CA220TO", "EG000AL", "GO000LE"};
	const char * lista_targhe[DEFAULT_N] = {
		"AA111AA", "BB222BB", "CC333CC", "DD444DD", "EE555EE",
		"FF666FF", "GG777GG", "HH888HH", "II999II", "JJ000JJ",
		"FF566FF", "GG677GG", "HH988HH", "II299II", "JJ100JJ", //ripetuti sin da qua
	};
	int i;
	for (i=0; i<DEFAULT_N; i++)
		insert_car(lista_targhe[i]);
}

void print_car_list()
{
	int i;
	for (i=0; i<MAX_FLOORS; i++)
		print_car_rec(i);
}

//Una funzione che prende in input un numero di piano e stampa le targhe
//di tutte le auto parcheggiate nel piano;
void print_car_rec(int id)
{
	lpCar tmp = carpark[id];
	if (tmp!=NULL)
		printf("%3d", id);
	else
		return;
	while (tmp!=NULL)
	{
		printf(" -> ");
		print_cars(tmp);
		tmp = tmp->next;
	}
	printf("\n");
}

void print_cars(const Car * node)
{
	if (node!=NULL)
		print_car(node->plate_number);
}

void print_car(const char * plate_number)
{
	if (plate_number!=NULL)
		printf("%s", plate_number);
}

//La funzione hash;
int hash_code(const char * plate_number)
{
	int res = 0;
	int len = strlen(plate_number);
	int i;
	for (i=0; i<len; i++)
		res += plate_number[i];
	return res % MAX_FLOORS;
}

//Una funzione che permette di inserire una nuova auto (in O(1) );
void insert_car(const char * plate_number)
{
	int h = hash_code(plate_number);
	carpark[h] = insert_car_coda(carpark[h], plate_number);
}

Car * insert_car_testa(Car * node, const char * plate_number)
{
	Car * testa = calloc(sizeof(Car), 1);
	testa->plate_number = plate_number;
	testa->next = node;
	return testa;
}

Car * insert_car_coda(Car * node, const char * plate_number)
{
	Car * tmp = node;
	while (tmp!=NULL && tmp->next!=NULL)
		tmp = tmp->next;
	if (tmp==NULL) //testa
		return insert_car_testa(node, plate_number);
	tmp->next = insert_car_testa(NULL, plate_number);
	return node;
}

//Una funzione che permette di cercare un’auto nel parcheggio
//(prendendo in input il suo numero di targa) e restituisce il puntatore a
//nodo (Car*) che la rappresenta;
lpCar search_car(const char * plate_number)
{
	int i;
	int h = hash_code(plate_number);
	lpCar node = carpark[h];
	while (node!=NULL)
	{
		if (node->plate_number==plate_number)
			return node;
		node = node->next;
	}
	return NULL;
}

//Una funzione che permette di eliminare un’automobile dal parcheggio.
void delete_car(const char * plate_number)
{
	int h = hash_code(plate_number);
	carpark[h] = delete_car_node(carpark[h], plate_number);
}

lpCar delete_car_node(Car * node, const char * plate_number)
{
	lpCar prev_tmp = NULL;
	int h = hash_code(plate_number);
	lpCar tmp = node;
	while (tmp!=NULL)
	{
		if (tmp->plate_number==plate_number)
		{
			// testa
			if (prev_tmp==NULL)
			{
				prev_tmp = tmp;
				tmp = tmp->next;
				free(prev_tmp);
				return tmp;
			}
			else
			{
				prev_tmp->next = (tmp!=NULL) ? tmp->next : NULL;
				free(tmp);
				break;
			}
		}
		prev_tmp = tmp;
		tmp = tmp->next;
	}
	return node;
}

