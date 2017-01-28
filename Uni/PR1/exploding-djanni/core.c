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
		clear_input();

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
	clear_input();

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

	return core_load_default_deck(pPlayers, pDeck, pStatus, mode_choice); // it will return false in case of failure
}

_Bool core_load_default_deck(Player pPlayers[], CardDeck * pDeck, GameStatus * pStatus, DifficultyMode mode_choice)
{
	// list of the relative decks
	static const char deckFileList[DIFFICULTY_MODE_NUM][DECKS_PATH_LEN] = {"decks/explodingDjanniEasy.txt", "decks/explodingDjanniHard.txt", "decks/explodingDjanniMedium.txt"};
	FILE * fpDeck = NULL;
	CardCount cardcount = {0, 0, 0};
	int i;
	Card tmp_card;
	CardNode * exploding_djanni_cards = NULL;
	CardNode * meooow_cards = NULL;
	CardNode * other_cards = NULL;

	// check to prevent out-of-range issues (note: mode_choice is unsigned)
	if (mode_choice >= DIFFICULTY_MODE_NUM)
		return false;

    // open the deck file in read mode
	fpDeck = fopen(deckFileList[mode_choice], "r");
	if (fpDeck == NULL) // exit in case of failure
	{
		// log_write("the deck file %s couldn't be open", deckFileList[mode_choice]);
		log_write("the deck file couldn't be open");
		return false;
	}

    // process the first line of the file (counter header)
	if (fscanf(fpDeck, "%d %d %d", &cardcount.n_exploding_djanni, &cardcount.n_meooow, &cardcount.n_other_cards)==0)
	{
		// log_write("the deck file %s couldn't be open", deckFileList[mode_choice]);
		log_write("the deck file header couldn't be processed");
		return false;
	}

	printf("total available cards: exploding djanni %d, meooow %d, others %d\n", cardcount.n_exploding_djanni, cardcount.n_meooow, cardcount.n_other_cards);

	return true;
}

