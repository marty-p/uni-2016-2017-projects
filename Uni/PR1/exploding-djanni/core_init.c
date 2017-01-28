#include "core_init.h"

_Bool core_init(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	char menu_choice;
	_Bool wrong_choice;

	do
	{
		wrong_choice = false;

		printf("What do you want to do? (1/2/q)\n");
		printf("\t1. Start a new game\n");
		printf("\t2. Load a saved game\n");
		printf("\tq. Exit\n");

		// ask which choice to make
		scanf("%c", &menu_choice);
		clear_input_line();

		// process the choice
		switch (menu_choice)
		{
			case '1':
				log_write("starting a new game...");
				// it will return false if quitted or failed reading the txt files:
				if (core_init_new_game(pPlayers, players_count, pDeck, pStatus) == false)
					return false;
				break;
			case '2':
				log_write("loading a saved game...");
				break;
			case 'q':
				log_write("exit confirmed...");
				return false;
				break;
			default: // if it's not in the list, we'll repeat it
				wrong_choice = true;
				break;
		}
	}
	while (wrong_choice==true);

	return true;
}

_Bool core_init_new_game(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	core_init_default_players(pPlayers, players_count);
	core_init_default_status(pStatus, pPlayers, players_count);

	return core_load_default_deck(pPlayers, players_count, pDeck, core_init_choose_mode()); // it will return false in case of failure
}

DifficultyMode core_init_choose_mode()
{
	DifficultyMode mode_choice;
	do
	{
		printf("In which mode do you want to start the game? (%d/%d/%d)\n", EASY, MEDIUM, HARD);
		printf("\t%d. Easy\n", EASY);
		printf("\t%d. Medium\n", MEDIUM);
		printf("\t%d. Hard\n", HARD);

		// ask which choice to make
		scanf("%u", &mode_choice);
		clear_input_line();

	}
	while (mode_choice >= DIFFICULTY_MODE_NUM); // note: it's unsigned (repeat if invalid)

	log_write("%s difficulty mode chosen...", get_difficulty_mode_name(mode_choice));
	return mode_choice;
}

_Bool core_init_default_status(GameStatus * pStatus, Player pPlayers[], int players_count)
{
	int i; // player's iter counter
	int is_somebody_alive = false; // if there's someone still alive, it will return true
	int random_turn; // dummy variable to pickup a valid turn
	if (pStatus!=NULL && pPlayers!=NULL)
	{
		// reset the status information
		pStatus->is_attacked = false;
		pStatus->player_turn = 0;
		pStatus->total_turns = 0;
		// check if there's someone still alive
		for (i=0; i<players_count && is_somebody_alive==false; i++)
			if (pPlayers[i].is_alive==true)
				is_somebody_alive = true;
		// skip if they are all dead
		if (is_somebody_alive)
		{
			// decide a random turn from the still alive players
			do
			{
				random_turn = get_random_number(0, players_count);
			}
			while (pPlayers[random_turn].is_alive==false); // repeat if the chosen player is dead

			pStatus->player_turn = random_turn; // assign the turn
		}
	}
	return is_somebody_alive;
}

void core_init_default_players(Player pPlayers[], int players_count)
{
	int i;
	char dummychar;

	log_write("initializing the players...");
	if (pPlayers!=NULL) // skip null ptr
	{
		for (i=0; i<players_count; i++)
		{
			printf("Setting up the #%d player:\n", i+1);

			// grab the name
			do
			{
				printf("Choose the player's name:\n");
				scanf("%23s", pPlayers[i].name);
				clear_input_line();
			}
			while (strlen(pPlayers[i].name)==0); // repeat if empty

#ifdef _DEBUG
			// choose whether being alive or not in debug mode
			printf("Choose whether the player must be alive or not: (any:yes, n:no)\n");
			scanf("%c", &dummychar);
			clear_input_line();
			pPlayers[i].is_alive = (dummychar!='n');
#endif

			// choose the type
			do
			{
				printf("Choose the player's type: (AI:%d/REAL:%d)\n", AI, REAL);
				scanf("%u", &pPlayers[i].type);
				clear_input_line();
			}
			while (pPlayers[i].type >= PLAYER_TYPE_NUM); // note: it's unsigned (repeat if invalid)

			// null inizialize the rest
			card_node_free(pPlayers[i].card_list);
			pPlayers[i].card_list = NULL;
			pPlayers[i].card_count = 0;

			log_write("Player #%d: name: %s, is_alive: %d, type: %s [%d]", i+1, pPlayers[i].name, pPlayers[i].is_alive, get_player_type_name(pPlayers[i].type), pPlayers[i].type);
		}
	}
}

_Bool core_load_default_deck(Player pPlayers[], int players_count, CardDeck * pGivenDeck, DifficultyMode mode_choice)
{
	// list of the relative decks' filenames
	static const char * deckFileList[DIFFICULTY_MODE_NUM] = {"decks/explodingDjanniEasy.txt", "decks/explodingDjanniMedium.txt", "decks/explodingDjanniHard.txt"};
	FILE * fpDeck = NULL; // file pointer to deck
	CardCount cc = { { {0, NULL}, {0, NULL}, {0, NULL}, } }; // resulting structure of the textual deck files
	int i, j; // temp variable used when itering
	Card tmp_card; // temp variable used when itering

	// check to prevent out-of-range issues (note: mode_choice is unsigned)
	if (mode_choice >= DIFFICULTY_MODE_NUM)
		return false;

	// open the deck file in read mode
	fpDeck = fopen(deckFileList[mode_choice], "r");
	if (fpDeck == NULL) // exit in case of failure
	{
		log_write("the deck file %s couldn't be open", deckFileList[mode_choice]);
		return false;
	}

	// process the first line of the file (counter header)
	if (fscanf(fpDeck, "%d %d %d", &cc.cards[N_EXPLODING_DJANNI].count, &cc.cards[N_MEOOOW].count, &cc.cards[N_OTHER_CARDS].count)!=3)
	{
		log_write("the deck file header couldn't be processed");
		return false;
	}

	log_write("total available cards: exploding djanni %d, meooow %d, others %d", cc.cards[N_EXPLODING_DJANNI].count, cc.cards[N_MEOOOW].count, cc.cards[N_OTHER_CARDS].count);

	log_write("start processing the deck file...");
	// iter every deck (exploding djanni, meooow, others)
	for (i=0; i<CARD_COUNT_NUM; i++)
	{
		// iter each deck's cards
		for (j=0; !feof(fpDeck) && j < cc.cards[i].count; j++)
		{
			// scan type and title and exit in case of failure
			if (fscanf(fpDeck, "%u %127[^\n]s", &tmp_card.type, tmp_card.title)!=2)
			{
				log_write("an error occurred when reading the deck file [i: %d, j: %d]", i, j);
				return false;
			}
			clear_file_input_line(fpDeck); // clear the remaining bytes of the line
			cc.cards[i].card_list = card_node_insert_tail(cc.cards[i].card_list, tmp_card); // adding the card in the relative deck
#ifdef _DEBUG
			log_write("added in deck list [%d]%s: %s", tmp_card.type, get_card_type_name(tmp_card.type), tmp_card.title);
#endif
		}
		// redundant check in case we encountered EOF or other runtime errors
		if (j != cc.cards[i].count || cc.cards[i].count != card_node_count(cc.cards[i].card_list))
		{
			log_write("an error occurred when finished to read the deck file [j: %d, count: %d, note count: %d]", j, cc.cards[i].count, card_node_count(cc.cards[i].card_list));
			return false;
		}
	}

	core_shuffle_deck(&cc.cards[N_OTHER_CARDS]); // shuffle the other cards
	core_assign_default_deck(pPlayers, players_count, &cc.cards[N_OTHER_CARDS], STARTING_OTHER_CARDS_NUM); // assign the 4 cards for each players
	core_assign_default_deck(pPlayers, players_count, &cc.cards[N_MEOOOW], STARTING_MEOOOW_NUM); // assign a meooow for each player
	return true;
}

void core_assign_default_deck(Player pPlayers[], int players_count, CardDeck * pGivenDeck, int given_cards)
{
}

