#include "core.h"

void core_run()
{
	Player players[PLAYER_COUNT] = {{{0}}};
	CardDeck deck = {0};
	GameStatus status = {0};

	log_write("initializing the game..."); // setting up the whole environment
	if (core_init(players, PLAYER_COUNT, &deck, &status)==true)
	{
		// start the game
	}
	// last operation (free memory)
	log_write("shutdowning the game...");
	core_shutdown(players, PLAYER_COUNT, &deck);
}

void core_shutdown(Player pPlayers[], int players_count, CardDeck * pDeck)
{
	int i; // counter
	// free every player's card list
	if (pPlayers!=NULL) // skip null ptr
	{
		for (i=0; i<players_count; i++)
		{
			card_node_free(pPlayers[i].card_list);
			pPlayers[i].card_list = NULL;
		}
	}
	// free the deck list
	if (pDeck!=NULL) // skip null ptr
	{
		card_node_free(pDeck->card_list);
		pDeck->card_list = NULL;
	}
}

void core_shuffle_deck(CardDeck * pGivenDeck)
{
}

const char * get_card_type_name(CardType card_type)
{
	static const char * name_list[CARD_TYPE_NUM] = {
		"EXPLODING DJANNI",
		"MEOOOW",
		"SHUFFLE",
		"NOPE",
		"SEE THE FUTURE",
		"ATTACK",
		"SKIP",
		"FAVOR",
		"DJANNI CARDS",
	};
	// prevent out-of-range issues
	if (card_type >= CARD_TYPE_NUM) // note: it's unsigned
		return "";
	return name_list[card_type];
}

const char * get_player_type_name(PlayerType player_type)
{
	static const char * name_list[PLAYER_TYPE_NUM] = {
		"AI",
		"REAL",
	};
	// prevent out-of-range issues
	if (player_type >= PLAYER_TYPE_NUM) // note: it's unsigned
		return "";
	return name_list[player_type];
}

const char * get_card_count_type_name(CardCountType card_count_type)
{
	static const char * name_list[CARD_COUNT_NUM] = {
		"N_EXPLODING_DJANNI",
		"N_MEOOOW",
		"N_OTHER_CARDS",
	};
	// prevent out-of-range issues
	if (card_count_type >= CARD_COUNT_NUM) // note: it's unsigned
		return "";
	return name_list[card_count_type];
}

const char * get_difficulty_mode_name(DifficultyMode difficulty_mode)
{
	static const char * name_list[DIFFICULTY_MODE_NUM] = {
		"EASY",
		"MEDIUM",
		"HARD",
	};
	// prevent out-of-range issues
	if (difficulty_mode >= DIFFICULTY_MODE_NUM) // note: it's unsigned
		return "";
	return name_list[difficulty_mode];
}

