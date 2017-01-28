#include "core.h"

void core_run()
{
	char menu_choice;
	_Bool wrong_choice;

	Player players[PLAYER_COUNT];
	CardDeck deck;
	GameStatus status;

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
				if (core_init_new_game(players, &deck, &status) == false)
					return;
				break;
			case '2':
				log_write("loading a saved game...");
				break;
			case 'q':
				log_write("exit confirmed...");
				return;
				break;
			default: // if it's not in the list, we'll repeat it
				wrong_choice = true;
				break;
		}
	} while (wrong_choice==true);
}

_Bool core_init_new_game(Player pPlayers[], CardDeck * pDeck, GameStatus * pStatus)
{
	DifficultyMode mode_choice;

	printf("In which mode do you want to start the game? (%d/%d/%d)\n", EASY, MEDIUM, HARD);
	printf("\t%d. Easy\n", EASY);
	printf("\t%d. Medium\n", MEDIUM);
	printf("\t%d. Hard\n", HARD);
	printf("Any other answer will make the game quit!\n");

	// ask which choice to make
	scanf("%u", &mode_choice);
	clear_input_line();

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
		default:
			log_write("exit confirmed...");
			return false;
			break;
	}

    core_assign_default_status(pStatus);
    core_assign_default_players(pPlayers);
	return core_load_default_deck(pPlayers, pDeck, mode_choice); // it will return false in case of failure
}

void core_assign_default_status(GameStatus * pStatus)
{
    if (pStatus!=NULL)
    {
        pStatus->is_attacked = false;
        pStatus->turn = 0;
    }
}

void core_assign_default_players(Player pPlayers[])
{
}

void core_assign_default_deck(Player pPlayers[], CardDeck * pGivenDeck, int given_cards)
{
}

_Bool core_load_default_deck(Player pPlayers[], CardDeck * pGivenDeck, DifficultyMode mode_choice)
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
			printf("%d: %s\n", tmp_card.type, tmp_card.title); //todo:variadic
		}
		// redundant check in case we encountered EOF
		if (j != cc.cards[i].count)
		{
			log_write("an error happened when finished to read the deck file"); //todo:variadic
			printf("%d != %d\n", j, cc.cards[i].count); //todo:variadic
			return false;
		}
	}

    core_assign_default_deck(pPlayers, &cc.cards[N_OTHER_CARDS], STARTING_OTHER_CARDS_NUM);
    core_assign_default_deck(pPlayers, &cc.cards[N_MEOOOW], STARTING_MEOOOW_NUM);
	return true;
}

