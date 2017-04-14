#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_TITLE 50
#define DIM_GENRE 50
#define DIM_NAME 50

//struttura che rappresenta una CANZONE
typedef struct song
{
	char title[DIM_TITLE];
	char genre[DIM_GENRE];
	float length;
	struct song* prev;
	struct song* next;
} Song;

//struttura che rappresenta una PLAYLIST
typedef struct playlist
{
	char name[DIM_NAME];
	Song* top;
} PlayList;

//funzioni (gia' definite) per l'acquisizione e per la stampa di una canzone
Song* acquireSong(); //acquisisce i dati di UNA canzone chiedendoli all'utente
Song* acquireSong2(const char* name); //acquisisce i dati di UNA canzone chiedendoli da arg
Song* copySong(const Song* s);
void insertSong(PlayList* pl, Song* s);
Song* findSong(PlayList* pl, char title[]);
void modifySong(PlayList* pl, Song* s);
void deleteSong(PlayList* pl, Song* s);
void printPlayList(PlayList* pl);
void printSong(Song* s); //stampa i dati relativi ad UNA canzone (passata tramite puntatore)
Song* nextSong(Song* s);
Song* prevSong(Song* s);
void mergePlayList(PlayList* plA, PlayList* plB, PlayList* plC);

//prototipi funzioni STUDENTE
//...

int main()
{
  //Creazione di una PLAYLIST. Utilizzare e riempire questa playlist
	PlayList p = {};
	strcpy(p.name, "Djanny Songs");
	p.top = NULL;
	PlayList p2 = {"Beta", NULL};
	PlayList p3 = {"Crucco", NULL};
	//altre chiamate e istruzioni per testare il funzionamento delle funzioni create
	//...
	printPlayList(&p); // nothing printed
	insertSong(&p, acquireSong2("Numb"));
	printf("***UPDATED***\n");
	printPlayList(&p);
	insertSong(&p, acquireSong2("In the end"));
	printf("***UPDATED***\n");
	printPlayList(&p);
	insertSong(&p, acquireSong2("Crawling"));
	printf("***UPDATED***\n");
	printPlayList(&p);
	insertSong(&p, acquireSong2("Castle of Glass"));
	printf("***UPDATED***\n");
	printPlayList(&p);

	//modifySong(&p, findSong(&p, "Crawling"));
	//printf("***UPDATED***\n");
	//printPlayList(&p);

	//deleteSong(&p, findSong(&p, "Crawling"));
	//deleteSong(&p, findSong(&p, "Castle of Glass"));
	//deleteSong(&p, findSong(&p, "In the end"));
	//printf("***UPDATED***\n");
	//printPlayList(&p);

	insertSong(&p2, acquireSong2("Dadadada"));
	insertSong(&p2, acquireSong2("Babababa"));
	insertSong(&p2, acquireSong2("Cacacaca"));
	mergePlayList(&p, &p2, &p3);
	printf("***UPDATED***\n");
	printPlayList(&p3);
	return 0;
}

/* ---------------------------------------------
* funzioni da NON modificare
* --------------------------------------------*/
//chiede all’utente i dati relativi ad una nuova canzone, alloca e
//riempie il nuovo nodo e ne restituisce il puntatore
Song* acquireSong()
{
	Song* new_s = (Song*)malloc(sizeof(Song));
	printf("\nInsert title -> ");
	scanf("%[^\n]s", new_s->title);
	getchar();

	printf("Insert genre -> ");
	scanf("%[^\n]s", new_s->genre);
	getchar();

	printf("Insert length -> ");
	scanf("%f", &(new_s->length));
	getchar();

	new_s->prev = NULL;
	new_s->next = NULL;

	return new_s;
}

Song* acquireSong2(const char* name)
{
	Song* new_s = (Song*)malloc(sizeof(Song));
	strncpy(new_s->title, name, sizeof(new_s->title));
	strncpy(new_s->genre, "Linkin Park", sizeof(new_s->title));
	new_s->length = 420.0;
	return new_s;
}

Song* copySong(const Song* song)
{
	if (song==NULL)
		return NULL;
	Song* new_s = (Song*)malloc(sizeof(Song));
	strncpy(new_s->title, song->title, sizeof(new_s->title));
	strncpy(new_s->genre, song->genre, sizeof(new_s->title));
	new_s->length = song->length;
	return new_s;
}

//inserisce una canzone (creata con la funzione acquire) nella lista
//in maniera ordinata
void insertSong(PlayList* pl, Song* s)
{
	Song* tmp_prev = NULL;
	Song* tmp_next = NULL;
	if (pl==NULL)
		return;
	if(pl->top==NULL)
	{
		pl->top = s;//<gestire il caso per la lista vuota>
		pl->top->prev = NULL;
		pl->top->next = NULL;
	}
	else
	{
		//ricerca della posizione in cui inserire
		//(tmp_prev e tmp_next sono due puntatori d’appoggio)
		tmp_prev = NULL;
		tmp_next = pl->top; //testa della playlist
		while (tmp_next != NULL && strcmp(tmp_next->title, s->title)<=0) //attenzione al confronto tra stringhe!
		{
			tmp_prev = tmp_next;
			tmp_next = tmp_next->next;
		}
		//ora conosciamo il nodo a cui appendere il nuovo nodo t
		if (tmp_next==NULL && tmp_prev!=NULL)
		{
			// <gestire il caso di inserimento in coda>
			tmp_next = s;
			tmp_next->prev = tmp_prev;
			tmp_next->next = NULL;
			tmp_prev->next = tmp_next;
		}
		else if (tmp_prev==NULL) //(dobbiamo inserire prima del primo elemento della playlist) then
		{
			//<gestire il caso di inserimento in testa>
			s->next = pl->top;
			s->prev = NULL;
			pl->top->prev = s;
			pl->top = s;
		}
		else
		{
			//<gestire il caso di inserimento generico tra due nodi>
			s->next = tmp_next;
			s->prev = tmp_prev;
			tmp_prev->next = s;
			tmp_next->prev = s;
		}
	}
}

//cerca una canzone nella lista (tramite il titolo) e restituisce il
//suo puntatore
Song* findSong(PlayList* pl, char title[])
{
	Song * tmp = NULL;
	if (pl==NULL)
		return NULL;
	tmp = pl->top;
	while (tmp!=NULL && strcmp(tmp->title, title)) // <=0 since it's sorted
		tmp = tmp->next;
	return tmp;
}

//modifica una canzone gia’ presente (trovata tramite la funzione
//findSong) e la riposiziona nella posizione corretta
void modifySong(PlayList* pl, Song* s)
{
	Song * tmp = NULL;
	Song song_copy = {};
	if (pl==NULL || s==NULL)
		return;
	song_copy = *s;
	deleteSong(pl, s);
	printf("You have the follownig song:\n");
	printSong(&song_copy);
	printf("Choose a new name for it:\n");
	scanf("%[^\n]49s", song_copy.title);
	insertSong(pl, acquireSong2(song_copy.title));
}

//elimina una canzone gia’ presente (trovata tramite la funzione
//findSong) e dealloca l’elemento
void deleteSong(PlayList* pl, Song* s)
{
	if (pl==NULL || s==NULL)
		return;
	if (s->next==NULL && s->prev!=NULL) // coda
	{
		s->prev->next = NULL;
	}
	else if (s->prev==NULL) // testa
	{
		pl->top = s->next;
		if (pl->top!=NULL)
			pl->top->prev = NULL;
	}
	else // mezzo
	{
		if (s->prev)
			s->prev->next = s->next;
		if (s->next)
			s->next->prev = s->prev;
	}
	free(s);
}

//stampa l’intera playlist di canzoni
void printPlayList(PlayList* pl)
{
	Song * tmp = NULL;
	if (pl==NULL)
		return;
	tmp = pl->top;
	while (tmp!=NULL)
	{
		printSong(tmp);
		tmp = tmp->next;
	}
}

//stampa le informazioni relative ad una singola canzone
void printSong(Song* t)
{
	printf("TITLE	:\t %s \n", t->title);
	printf("GENRE	:\t %s \n", t->genre);
	printf("LENGTH   :\t %f \n\n", t->length);
//#ifdef _DEBUG
	printf("PREV   :\t %p \n\n", t->prev);
	printf("THIS   :\t %p \n\n", t);
	printf("NEXT   :\t %p \n\n", t->next);
//#endif
}

//restituisce il puntatore alla canzone successiva rispetto a quella
//passata come puntatore se presente, altrimenti restituisce NULL
Song* nextSong(Song* s)
{
	if (s==NULL)
		return NULL;
	return s->next;
}

//restituisce il puntatore alla canzone precedente rispetto a quella
//passata come puntatore se presente, altrimenti restituisce NULL
Song* prevSong(Song* s)
{
	if (s==NULL)
		return NULL;
	return s->prev;
}
/* ---------------------------------------------
* funzioni STUDENTE
* --------------------------------------------*/
//...

//fonde le liste plA e plB in un’unica lista plC (anch’essa passata come parametro). NESSUN nuovo
//nodo deve essere allocato
void mergePlayList(PlayList* plA, PlayList* plB, PlayList* plC)
{
	Song * tmp = NULL;
	if (plA==NULL || plB==NULL)
		return;

	while (plA->top!=NULL || plB->top!=NULL)
	{
		if (plA->top!=NULL && plB->top!=NULL)
		{
			// pop from A
			if (strcmp(plA->top->title, plB->top->title)<=0)
			{
				tmp = plA->top->next;
				plA->top->prev = NULL;
				plA->top->next = NULL;
				insertSong(plC, plA->top);
				plA->top = tmp;
				plA->top->prev = NULL;
			}
			// pop from B
			else
			{
				tmp = plB->top->next;
				plB->top->prev = NULL;
				plB->top->next = NULL;
				insertSong(plC, plB->top);
				plB->top = tmp;
				if (plB->top!=NULL)
					plB->top->prev = NULL;
			}
		}
		// pop from A
		else if (plA->top!=NULL && plB->top==NULL)
		{
			tmp = plA->top->next;
			plA->top->prev = NULL;
			plA->top->next = NULL;
			insertSong(plC, plA->top);
			plA->top = tmp;
			if (plA->top!=NULL)
				plA->top->prev = NULL;
		}
		// pop from B
		else if (plA->top==NULL && plB->top!=NULL)
		{
			tmp = plB->top->next;
			plB->top->prev = NULL;
			plB->top->next = NULL;
			insertSong(plC, plB->top);
			plB->top = tmp;
			plB->top->prev = NULL;
		}
	}
}
