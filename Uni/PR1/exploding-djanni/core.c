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
		if (core_game_start(players, PLAYER_COUNT, &deck, &status)==true)
			core_game_print_winners(players, PLAYER_COUNT);
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
#ifdef _DEBUG
	deck_log_print_cards(pGivenDeck);
#endif
	if (pGivenDeck!=NULL) // skip null ptr
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
			// swapping values
			tmp_card = *cards[i];
			*cards[i] = *cards[random_number];
			*cards[random_number] = tmp_card;
		}

		// freeing the memory to prevent memory leaks
		free(cards);
		log_write("the deck has been shuffled");
	}
#ifdef _DEBUG
	deck_log_print_cards(pGivenDeck);
#endif
}

void core_shuffle_deck_head(CardDeck * pGivenDeck)
{
	Card first_card = {{0}};
	int random_number; // dummy variable for random numbers

	if (pGivenDeck!=NULL && pGivenDeck->card_list!=NULL && pGivenDeck->card_list->next!=NULL) // skip null ptr or if the deck's length is <=1
	{
		first_card = pGivenDeck->card_list->card; // save first
		core_remove_deck_head(pGivenDeck); // remove first
		random_number = get_random_number(0, pGivenDeck->count); // it will stop count-1, so it should be safe not decreasing count by 1 in here
		core_insert_deck_in_n(pGivenDeck, first_card, random_number); //re-add first
	}
}

void core_insert_deck_in_n(CardDeck * pGivenDeck, Card card, int n)
{
	CardNode * tmp = NULL; // points to given_deck->card_list->head
	CardNode * prevtmp = NULL;
	int count = 0;
	if (pGivenDeck!=NULL)
	{
		tmp = pGivenDeck->card_list;
		while (tmp!=NULL && count<n)
		{
			prevtmp=tmp;
			tmp=tmp->next;
			count++;
		}
		if (count==n) // skip if doesn't match
		{
			if (prevtmp) // after head
			{
				prevtmp->next = card_node_insert_head(tmp, card);
				pGivenDeck->count++;
			}
			else // head
			{
				pGivenDeck->card_list = card_node_insert_head(tmp, card);
				pGivenDeck->count++;
			}
		}
	}
}

void core_remove_deck_n_card(CardDeck * pGivenDeck, int selected_card)
{
	_Bool is_removed = false;
	if (pGivenDeck!=NULL)
	{
		pGivenDeck->card_list = card_node_check_remove(pGivenDeck->card_list, selected_card, &is_removed);
		if (is_removed==true)
			pGivenDeck->count--; // keep O(1)
	}
}

void core_remove_deck_head(CardDeck * pGivenDeck)
{
	core_remove_deck_n_card(pGivenDeck, 0);
}

void core_remove_player_n_card(Player * pGivenPlayer, int selected_card)
{
	_Bool is_removed = false;
	if (pGivenPlayer!=NULL)
	{
		pGivenPlayer->card_list = card_node_check_remove(pGivenPlayer->card_list, selected_card, &is_removed);
		if (is_removed==true)
			pGivenPlayer->card_count--; // keep O(1)
	}
}

void core_remove_player_card_type(Player * pGivenPlayer, CardType card_type)
{
	_Bool is_removed = false;
	pGivenPlayer->card_list = card_node_find_first_n_type_and_delete(pGivenPlayer->card_list, card_type, &is_removed);
	if (is_removed==true)
		pGivenPlayer->card_count--; // keep O(1)
}

void core_remove_player_first_matched_card(Player * pGivenPlayer, Card copy_card)
{
	_Bool is_removed = false;
	pGivenPlayer->card_list = card_node_find_first_matched_card_and_delete(pGivenPlayer->card_list, copy_card, &is_removed);
	if (is_removed==true)
		pGivenPlayer->card_count--; // keep O(1)
}

_Bool core_player_has_in(Player * pGivenPlayer, CardType card_type)
{
	return card_node_find_first_n_type(pGivenPlayer->card_list, card_type, NULL)!=NULL;
}

void core_player_give_card_n_to_player(Player * pGiver, Player * pReceiver, int selected_card)
{
	CardNode * used_card = NULL;
	Card new_card = {{0}};
	CardNode * prev = NULL;
	_Bool is_deleted = false;
	if (pGiver!=NULL && pReceiver!=NULL) // skip null ptr
	{
		used_card = card_node_select_n(pGiver->card_list, selected_card, &prev);
		if (used_card==NULL) // have the player already lost that card?
			return;
		new_card = used_card->card;

		pGiver->card_list = card_node_check_remove(pGiver->card_list, selected_card, &is_deleted); // remove the giver's select card
		if (is_deleted==true)
		{
			pGiver->card_count--; // keep O(1) count updated
			pReceiver->card_list = card_node_insert_head(pReceiver->card_list, new_card); // add the giver's selected card into player's card_list
			pReceiver->card_count++; // keep O(1) card_count updated
		}
		else
			log_write("core_player_give_card_n_to_player failed\n");
	}
}

void core_player_draw_from_deck(Player * pPlayer, CardDeck * pGivenDeck)
{
	if (pPlayer!=NULL && pGivenDeck!=NULL) // skip null ptr
	{
		pPlayer->card_list = card_node_insert_head(pPlayer->card_list, pGivenDeck->card_list->card); // add the first given_deck's card into player's card_list
		pGivenDeck->card_list = card_node_remove_head(pGivenDeck->card_list); // remove the first given_deck's card
		pPlayer->card_count++; // keep O(1) card_count updated
		pGivenDeck->count--; // keep O(1) count updated
	}
}

int core_deck_count_of_type_n(const CardDeck * pGivenDeck, CardType card_type)
{
	if (pGivenDeck==NULL)
		return 0;
	return card_node_count_of_type_n(pGivenDeck->card_list, card_type);
}

double core_deck_get_pct_of_type_n(const CardDeck * pGivenDeck, CardType card_type)
{
	if (pGivenDeck==NULL)
		return 0.0;
	return (double)core_deck_count_of_type_n(pGivenDeck, card_type)/pGivenDeck->count*100.0;
}

int core_player_count_of_type_n(const Player * pGivenPlayer, CardType card_type)
{
	if (pGivenPlayer==NULL)
		return 0;
	return card_node_count_of_type_n(pGivenPlayer->card_list, card_type);
}

double core_player_get_pct_of_type_n(const Player * pGivenPlayer, CardType card_type)
{
	if (pGivenPlayer==NULL)
		return 0.0;
	return (double)core_player_count_of_type_n(pGivenPlayer, card_type)/pGivenPlayer->card_count*100.0;
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

const char * get_djanni_mode_name(DjanniMode djanni_mode)
{
	static const char * name_list[DJANNI_MODE_NUM] =
	{
		"SINGLE",
		"COUPLE",
		"TRIPLE",
	};
	// prevent out-of-range issues
	if (djanni_mode >= DJANNI_MODE_NUM) // note: it's unsigned
		return "";
	return name_list[djanni_mode]; // return the djanni mode type name as string
}

void players_log_data(const Player * pPlayers, int players_count)
{
	int i; // counter for iteration
	if (pPlayers!=NULL) // skip null ptr
	{
		for (i=0; i<players_count; i++) // iter all the players
		{
			// print the player's status and all the relative cards
			log_write("Player #%d's name: %s, is_alive: %d, type: [%u]%s", i+1, pPlayers[i].name, pPlayers[i].is_alive, pPlayers[i].type, get_player_type_name(pPlayers[i].type));
			log_write("List of the player #%d's cards: (count: %d==%d)", i+1, pPlayers[i].card_count, card_node_count(pPlayers[i].card_list));
			card_node_log_print(pPlayers[i].card_list);
		}
	}
}

void player_log_turn_data(const Player * pPlayer, const GameStatus * pStatus)
{
	if (pPlayer!=NULL && pStatus!=NULL) // skip null ptr
	{
		// log the player's status and the relative cards
		log_write("Turn #%d: Player #%d's name: %s, is_alive: %d, type: [%u]%s, is_attacked: %d", pStatus->total_turns, pStatus->player_turn+1, pPlayer->name, pPlayer->is_alive, pPlayer->type, get_player_type_name(pPlayer->type), pStatus->is_attacked);
		log_write("List of the player #%d's cards: (count: %d==%d)", pStatus->player_turn+1, pPlayer->card_count, card_node_count(pPlayer->card_list));
		card_node_log_print(pPlayer->card_list);
	}
}

void status_log_data(const GameStatus * pStatus)
{
	if (pStatus!=NULL) // skip null ptr
	{
		// log the player's status and the relative cards
		log_write("Turn #%d, Player #%d's turn, is_attacked: %d", pStatus->total_turns, pStatus->player_turn+1, pStatus->is_attacked);
	}
}

void player_print_hand(const Player * pPlayer)
{
	CardNode * tmp = pPlayer->card_list;
	int count=0;
	if (pPlayer==NULL) // skip null ptr
		return;

	while (tmp!=NULL) // skip null ptr
	{
		// print all its values
		printf("\t(%d) [%d]%s: %s\n", count, tmp->card.type, get_card_type_name(tmp->card.type), tmp->card.title);
		tmp = tmp->next;
		count++;
	}
}

void player_print_secret_hand(const Player * pPlayer)
{
	CardNode * tmp = pPlayer->card_list;
	int count=0;
	if (pPlayer==NULL) // skip null ptr
		return;

	while (tmp!=NULL) // skip null ptr
	{
		// print all its values
		printf("\t(%d) **********\n", count);
		tmp = tmp->next;
		count++;
	}
}

void player_print_n_card(const Player * pPlayer, int selected_card)
{
	CardNode * tmp = NULL;
	if (pPlayer==NULL) // skip null ptr
		return;

	tmp = card_node_select_n(pPlayer->card_list, selected_card, NULL);
	if (tmp!=NULL)
		printf("\t(%d) [%d]%s: %s\n", selected_card, tmp->card.type, get_card_type_name(tmp->card.type), tmp->card.title);
}

void player_log_print_n_card(const Player * pPlayer, int selected_card)
{
	CardNode * tmp = NULL;
	if (pPlayer==NULL) // skip null ptr
		return;

	tmp = card_node_select_n(pPlayer->card_list, selected_card, NULL);
	if (tmp!=NULL)
		log_write("\t(%d) [%d]%s: %s", selected_card, tmp->card.type, get_card_type_name(tmp->card.type), tmp->card.title);
}

void deck_print_count(const CardDeck * pDeck)
{
	if (pDeck!=NULL)
		printf("deck: (count %d==%d)\n", pDeck->count, card_node_count(pDeck->card_list));
}

void deck_log_print_count(const CardDeck * pDeck)
{
	if (pDeck!=NULL)
		log_write("deck: (count %d==%d)", pDeck->count, card_node_count(pDeck->card_list));
}

void deck_print_cards(const CardDeck * pDeck)
{
	deck_print_count(pDeck);
	card_node_print(pDeck->card_list);
}

void deck_log_print_cards(const CardDeck * pDeck)
{
	deck_log_print_count(pDeck);
	card_node_log_print(pDeck->card_list);
}

void deck_print_first_n_cards(const CardDeck * pDeck, int n)
{
	card_node_print_first_n(pDeck->card_list, n);
}

void deck_log_print_first_n_cards(const CardDeck * pDeck, int n)
{
	card_node_log_print_first_n(pDeck->card_list, n);
}

