#include "core.h"

void core_run(void)
{
	// default game variables:
	Player players[PLAYER_COUNT] = {{{0}}};
	CardDeck deck = {0};
	GameStatus status = {0};

	log_write("initializing the game..."); // setting up the whole environment
	if (core_init(players, PLAYER_COUNT, &deck, &status)==true)
	{
		// start the game
		log_write("starting the game...");
		core_game_start(players, PLAYER_COUNT, &deck, &status);
	}
	log_write("shutting down the game...");
	core_shutdown(players, PLAYER_COUNT, &deck); // last operation (free memory)
}

void core_shutdown(Player pPlayers[], int players_count, CardDeck * pDeck)
{
	int i; // counter
	// free every player's card list
	if (pPlayers!=NULL) // skip null ptr
	{
		for (i=0; i<players_count; i++) // iter all the players
		{
			card_node_free(pPlayers[i].card_list); // free their cards
			pPlayers[i].card_list = NULL; // reset the ptr
		}
	}
	// free the deck list
	if (pDeck!=NULL) // skip null ptr
	{
		card_node_free(pDeck->card_list); // free the deck cards
		pDeck->card_list = NULL; // reset the ptr
	}
}

void core_shuffle_deck(CardDeck * pGivenDeck)
{
	Card ** cards = NULL; // used to store all the cards' ptr for easy shuffling
	CardNode * tmp = NULL; // points to given_deck->card_list->head
	int i; // counter for iteration
	Card tmp_card; // dummy card for shifting values
	int random_number; // dummy variable for random numbers
	if (pGivenDeck!=NULL)
	{
		// create a dynamic array to temporary store all the cards
		cards = calloc(pGivenDeck->count, sizeof(Card*)); // deck.count==O(1) instead of card_node_count(deck.card_list)==O(n)
		if (cards==NULL)
			exit(EXIT_FAILURE); // exit in case of failure

		// save all the items in deck.card_list inside cards
		tmp = pGivenDeck->card_list;
		for (i=0; i<pGivenDeck->count && tmp!=NULL; i++, tmp=tmp->next)
			cards[i] = &tmp->card;

		// redundant check in case we encountered runtime errors
		if (i!=pGivenDeck->count)
		{
			log_write("an error occurred when started shuffling the deck [i: %d, count: %d, node count: %d]", i, pGivenDeck->count, card_node_count(pGivenDeck->card_list));
			free(cards); // free cards to prevent memory leaks
			return;
		}

		// shuffle algorithm
		for (i=0; i<pGivenDeck->count; i++)
		{
			// picking up a random value and skip if it's the same of the index
			random_number = get_random_number(0, pGivenDeck->count-1);
			if (random_number==i)
				continue;
			// shifting values
			tmp_card = *cards[i];
			*cards[i] = *cards[random_number];
			*cards[random_number] = tmp_card;
		}

		// freeing the memory to prevent memory leaks
		free(cards);
		log_write("the deck has been shuffled");
	}
}

const char * get_card_type_name(CardType card_type)
{
	static const char * name_list[CARD_TYPE_NUM] =
	{
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
	return name_list[card_type]; // return the card type name as string
}

const char * get_player_type_name(PlayerType player_type)
{
	static const char * name_list[PLAYER_TYPE_NUM] =
	{
		"AI",
		"REAL",
	};
	// prevent out-of-range issues
	if (player_type >= PLAYER_TYPE_NUM) // note: it's unsigned
		return "";
	return name_list[player_type]; // return the player type name as string
}

const char * get_card_count_type_name(CardCountType card_count_type)
{
	static const char * name_list[CARD_COUNT_NUM] =
	{
		"N_EXPLODING_DJANNI",
		"N_MEOOOW",
		"N_OTHER_CARDS",
	};
	// prevent out-of-range issues
	if (card_count_type >= CARD_COUNT_NUM) // note: it's unsigned
		return "";
	return name_list[card_count_type]; // return the card count type name as string
}

const char * get_difficulty_mode_name(DifficultyMode difficulty_mode)
{
	static const char * name_list[DIFFICULTY_MODE_NUM] =
	{
		"EASY",
		"MEDIUM",
		"HARD",
	};
	// prevent out-of-range issues
	if (difficulty_mode >= DIFFICULTY_MODE_NUM) // note: it's unsigned
		return "";
	return name_list[difficulty_mode]; // return the difficulty mode type name as string
}

void players_log_data(Player * pPlayers, int players_count)
{
	int i; // counter for iteration
	if (pPlayers!=NULL) // skip null ptr
	{
		for (i=0; i<players_count; i++) // iter all the players
		{
			// print the player's status and all the relative cards
			log_write("Player #%d's name: %s, is_alive: %d, type: [%u]%s", i+1, pPlayers[i].name, pPlayers[i].is_alive, pPlayers[i].type, get_player_type_name(pPlayers[i].type));
			log_write("List of the player #%d's cards: (count: %d)", i+1, pPlayers[i].card_count);
			card_node_log_print(pPlayers[i].card_list);
		}
	}
}

void player_log_data(Player * pPlayer, GameStatus * pStatus)
{
	if (pPlayer!=NULL && pStatus!=NULL) // skip null ptr
	{
		// log the player's status and the relative cards
		log_write("Turn #%d: Player #%d's name: %s, is_alive: %d, type: [%u]%s, is_attacked: %d", pStatus->total_turns, pStatus->player_turn, pPlayer->name, pPlayer->is_alive, pPlayer->type, get_player_type_name(pPlayer->type), pStatus->is_attacked);
		log_write("List of the player #%d's cards: (count: %d)", pStatus->player_turn, pPlayer->card_count);
		card_node_log_print(pPlayer->card_list);
	}
}

void status_log_data(GameStatus * pStatus)
{
	if (pStatus!=NULL) // skip null ptr
	{
		// log the player's status and the relative cards
		log_write("Turn #%d, Player #%d's turn, is_attacked: %d", pStatus->total_turns, pStatus->player_turn, pStatus->is_attacked);
	}
}

