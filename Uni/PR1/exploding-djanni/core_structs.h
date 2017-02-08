#ifndef __EDJ_CORE_STRUCTS_H__
#define __EDJ_CORE_STRUCTS_H__

#include "core.h"

/* enum list */
typedef enum
{
	EASY, //0
	MEDIUM, //1
	HARD //2
} DifficultyMode; // list of the decks' modes

typedef enum
{
	EXPLODING_DJANNI, //0
	MEOOOW, //1
	SHUFFLE, //2
	NOPE, //3
	SEE_THE_FUTURE, //4
	ATTACK, //5
	SKIP, //6
	FAVOR, //7
	DJANNI_CARDS //8
} CardType; // list of the cards' types

typedef enum
{
	REAL, //0
	AI //1
} PlayerType;

typedef enum
{
	N_EXPLODING_DJANNI, //0
	N_MEOOOW, //1
	N_OTHER_CARDS //2
} CardCountType; // list of the counts made in the decks' files

typedef enum
{
	DM_SINGLE, //0
	DM_COUPLE, //1
	DM_TRIPLE //2
} DjanniMode; // list of djanni cards' modes

/* struct list */
typedef struct
{
	char title[CARD_TITLE_LEN+1];
	CardType type;
} Card; // card struct

typedef struct CardNode
{
	Card card;
	struct CardNode * next;
} CardNode; // card node struct

typedef struct
{
	char name[PLAYER_NAME+1];
	_Bool is_alive; // true if not dead
	int card_count;
	PlayerType type;
	Card * cards;
} Player; // struct of a player... 1st block of the .sav file

typedef struct
{
	int count;
	CardNode * card_list;
} CardDeck; // struct of a deck... 2nd block of the .sav file

typedef struct
{
	int player_turn;
	_Bool is_attacked; // true if the player will repeat the turn
	int total_turns; // extra data
} GameStatus; // struct of the game status... 3rd block of the .sav file

typedef struct
{
	CardDeck cards[CARD_COUNT_NUM];
} CardCount; // list of card counts' decks

typedef struct
{
	_Bool has_attacked; // if the player has attacked
	_Bool is_noped; // if the card has been noped
	_Bool has_drawn; // if the player has drawn a card
	_Bool saw_terrible_future; // ai-related, if the ai saw a djanni card in the head of the deck (or 100% of drawing one)
	DjanniMode selected_djanni_mode; // ai-related, the djanni mode the ai chose
} GameEnv; // game environment (not stored in .sav)

#endif

