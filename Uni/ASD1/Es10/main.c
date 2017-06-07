#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENABLE_INPUT_MODE

#define MAX_FLOORS 10
#define PLATE_LEN 7
typedef struct car
{
	char * plate_number;
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
void insert_car(char * plate_number);
lpCar search_car(const char * plate_number);
void delete_car(const char * plate_number);
lpCar delete_car_node(Car * node, const char * plate_number);

Car * insert_car_testa(Car * node, char* plate_number);
Car * insert_car_coda(Car * node, char* plate_number);

void default_set();

#define IM_NUM 6
typedef enum {IM_INSERT, IM_SEARCH, IM_DELETE, IM_PRINT_ONE, IM_PRINT_ALL, IM_EXIT} ImType;
const char * get_input_name(ImType i);
void input_mode();
void input_insert(void);
void input_search(void);
void input_delete(void);
void input_print_one(void);
void input_print_all(void);
typedef void (*ImFnc)(void);
ImFnc inputFunc[IM_NUM] = {input_insert, input_search, input_delete, input_print_one, input_print_all, NULL};

int main()
{
#ifdef ENABLE_INPUT_MODE
	input_mode();
#else
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
#endif
	return 0;
}

const char * get_input_name(ImType i)
{
	static const char * names[IM_NUM] = {"Inserisci", "Ricerca", "Cancella", "Stampa Singolo", "Stampa Tutto", "ESCI"};
	if (i>=IM_NUM)
		return "";
	return names[i];
}

void input_mode()
{
	ImType i;
	do
	{
		printf("Che vuoi fare? (sbaglia per uscire)\n");
		for (i=0; i<IM_NUM; i++)
			printf("%u: %s\n", i, get_input_name(i));
		scanf("%u", &i);
		while (getchar()!='\n')
			continue;
		if (i>=IM_EXIT)
			break;
		inputFunc[i]();
	} while (i<IM_NUM);
}

void input_insert()
{
	char * plate_number = calloc(sizeof(char), PLATE_LEN+1);
	printf("Inserisci la targa da inserire: (len: %d)\n", PLATE_LEN);
	scanf("%7s", plate_number);
	getchar();
	insert_car(plate_number);
}

void input_search()
{
	char buf[PLATE_LEN+1] = {};
	printf("Inserisci la targa da ricercare: (len: %d)\n", PLATE_LEN);
	scanf("%7s", buf);
	getchar();
	lpCar nodo = search_car(buf);
	printf("nodo %s", (nodo) ? "trovato" : "non trovato");
}

void input_delete()
{
	char buf[PLATE_LEN+1] = {};
	printf("Inserisci la targa da cancellare: (len: %d)\n", PLATE_LEN);
	scanf("%7s", buf);
	getchar();
	delete_car(buf);
}

void input_print_one()
{
	int i;
	do
	{
		printf("Inserisci il piano da stampare: (max len: %d)\n", MAX_FLOORS);
		scanf("%d", &i);
		getchar();
	} while (i<0 || i>MAX_FLOORS);
	print_car_rec(i);
}

void input_print_all()
{
	printf("\n\n\n\n");
	print_car_list();
}

//#define DEFAULT_N 4
#define DEFAULT_N 15
void default_set()
{
	//const char * lista_targhe[DEFAULT_N] = {"PI555TA", "CA220TO", "EG000AL", "GO000LE"};
	char * lista_targhe[DEFAULT_N] = {
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
void insert_car(char * plate_number)
{
	int h = hash_code(plate_number);
	carpark[h] = insert_car_coda(carpark[h], plate_number);
}

Car * insert_car_testa(Car * node, char * plate_number)
{
	Car * testa = calloc(sizeof(Car), 1);
	testa->plate_number= plate_number;
	testa->next = node;
	return testa;
}

Car * insert_car_coda(Car * node, char * plate_number)
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
//	int i;
	int h = hash_code(plate_number);
	lpCar node = carpark[h];
	while (node!=NULL)
	{
		if (strcmp(node->plate_number, plate_number)==0)
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
//	int h = hash_code(plate_number);
	lpCar tmp = node;
	while (tmp!=NULL)
	{
		if (strcmp(tmp->plate_number, plate_number)==0)
		{
			// testa
			if (prev_tmp==NULL)
			{
				prev_tmp = tmp;
				tmp = tmp->next;
				free(prev_tmp->plate_number);
				free(prev_tmp);
				return tmp;
			}
			else
			{
				prev_tmp->next = (tmp!=NULL) ? tmp->next : NULL;
				free(tmp->plate_number);
				free(tmp);
				break;
			}
		}
		prev_tmp = tmp;
		tmp = tmp->next;
	}
	return node;
}

