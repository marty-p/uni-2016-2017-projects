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

