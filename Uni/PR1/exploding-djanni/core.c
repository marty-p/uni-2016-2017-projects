#include "core.h"

void core_run()
{
	Player players[PLAYER_COUNT] = {{{0}}};
	CardDeck deck = {0};
	GameStatus status = {0};

	log_write("initializing the game...");
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
	} while (wrong_choice==true);

    return true;
}

_Bool core_init_new_game(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{

    core_init_default_status(pStatus);
    core_init_default_players(pPlayers, players_count);

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

    } while (mode_choice >= DIFFICULTY_MODE_NUM);

	// process the choice
	switch (mode_choice)
	{
		case EASY:
			log_write("easy mode chosen...");
			break;
		case MEDIUM:
			log_write("medium mode chosen...");
			break;
		case HARD:
			log_write("hard mode chosen...");
			break;
	}
    return mode_choice;
}


void core_init_default_status(GameStatus * pStatus)
{
    if (pStatus!=NULL)
    {
        pStatus->is_attacked = false;
        pStatus->turn = 0;
    }
}

void core_shuffle_deck(CardDeck * pGivenDeck)
{
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
            do {
                printf("Choose the player's name:\n");
                scanf("%23s", pPlayers[i].name);
                clear_input_line();
            } while (strlen(pPlayers[i].name)==0); // repeat if empty

            // choose if alive
            printf("Choose whether the player must be alive or not: (any:yes, n:no)\n");
            scanf("%c", &dummychar);
            clear_input_line();
            pPlayers[i].is_alive = (dummychar!='n');

            // choose the type
            do {
                printf("Choose the player's type: (AI:%d/REAL:%d)\n", AI, REAL);
                scanf("%u", &pPlayers[i].type);
                clear_input_line();
            } while (pPlayers[i].type >= PLAYER_TYPE_NUM); // repeat if invalid

            // null inizialize the rest
            card_node_free(pPlayers[i].card_list);
            pPlayers[i].card_list = NULL;
            pPlayers[i].card_count = 0;
        }
    }
}

void core_assign_default_deck(Player pPlayers[], int players_count, CardDeck * pGivenDeck, int given_cards)
{
}

_Bool core_load_default_deck(Player pPlayers[], int players_count, CardDeck * pGivenDeck, DifficultyMode mode_choice)
{
	// list of the relative decks' filenames
	static const char deckFileList[DIFFICULTY_MODE_NUM][DECKS_PATH_LEN] = {"decks/explodingDjanniEasy.txt", "decks/explodingDjanniMedium.txt", "decks/explodingDjanniHard.txt"};
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
		// log_write("the deck file %s couldn't be open", deckFileList[mode_choice]); //todo:variadic
		log_write("the deck file couldn't be open");
		return false;
	}

    // process the first line of the file (counter header)
	if (fscanf(fpDeck, "%d %d %d", &cc.cards[N_EXPLODING_DJANNI].count, &cc.cards[N_MEOOOW].count, &cc.cards[N_OTHER_CARDS].count)!=3)
	{
		// log_write("the deck file %s couldn't be open", deckFileList[mode_choice]); //todo:variadic
		log_write("the deck file header couldn't be processed");
		return false;
	}

	printf("total available cards: exploding djanni %d, meooow %d, others %d\n", cc.cards[N_EXPLODING_DJANNI].count, cc.cards[N_MEOOOW].count, cc.cards[N_OTHER_CARDS].count); //todo:variadic

	// iter every deck (exploding djanni, meooow, others)
	for (i=0; i<CARD_COUNT_NUM; i++)
	{
		// iter each deck's cards
		for (j=0; !feof(fpDeck) && j < cc.cards[i].count; j++)
		{
			// scan type and title and exit in case of failure
			if (fscanf(fpDeck, "%u %127[^\n]s", &tmp_card.type, tmp_card.title)!=2)
			{
				log_write("an error happened when reading the deck file"); //todo:variadic
				return false;
			}
			clear_file_input_line(fpDeck); // clear the remaining bytes of the line
			cc.cards[i].card_list = card_node_insert_tail(cc.cards[i].card_list, tmp_card); // adding the card in the relative deck
#ifdef _DEBUG
			printf("%d: %s\n", tmp_card.type, tmp_card.title); //todo:variadic
#endif
		}
		// redundant check in case we encountered EOF or other runtime errors
		if (j != cc.cards[i].count || cc.cards[i].count != card_node_count(cc.cards[i].card_list))
		{
			log_write("an error happened when finished to read the deck file"); //todo:variadic
#ifdef _DEBUG
			printf("%d != %d != %d\n", j, cc.cards[i].count, card_node_count(cc.cards[i].card_list)); //todo:variadic
#endif
			return false;
		}
	}

    core_shuffle_deck(&cc.cards[N_OTHER_CARDS]);
    core_assign_default_deck(pPlayers, players_count, &cc.cards[N_OTHER_CARDS], STARTING_OTHER_CARDS_NUM);
    core_assign_default_deck(pPlayers, players_count, &cc.cards[N_MEOOOW], STARTING_MEOOOW_NUM);
	return true;
}

