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

	return core_load_default_deck(pPlayers, pDeck, pStatus, mode_choice); // it will return false in case of failure
}

_Bool core_load_default_deck(Player pPlayers[], CardDeck * pDeck, GameStatus * pStatus, DifficultyMode mode_choice)
{
	// list of the relative decks' filenames
	static const char deckFileList[DIFFICULTY_MODE_NUM][DECKS_PATH_LEN] = {"decks/explodingDjanniEasy.txt", "decks/explodingDjanniMedium.txt", "decks/explodingDjanniHard.txt"};
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
		// log_write("the deck file %s couldn't be open", deckFileList[mode_choice]); //todo:variadic
		log_write("the deck file couldn't be open");
		return false;
	}

    // process the first line of the file (counter header)
	if (fscanf(fpDeck, "%d %d %d", &cardcount.n_exploding_djanni, &cardcount.n_meooow, &cardcount.n_other_cards)!=3)
	{
		// log_write("the deck file %s couldn't be open", deckFileList[mode_choice]); //todo:variadic
		log_write("the deck file header couldn't be processed");
		return false;
	}

	printf("total available cards: exploding djanni %d, meooow %d, others %d\n", cardcount.n_exploding_djanni, cardcount.n_meooow, cardcount.n_other_cards); //todo:variadic

    // iter all the exploding djanni cards
	for (i=0; !feof(fpDeck) && i < cardcount.n_exploding_djanni; i++)
	{
	    // scan type and title and exit in case of failure
        if (fscanf(fpDeck, "%u %31[^\n]s", &tmp_card.type, tmp_card.title)!=2)
        {
            log_write("an error happened when reading the deck file (exploding djanni lines)");
            return false;
        }
		clear_file_input_line(fpDeck); // clear the remaining bytes of the line
        exploding_djanni_cards = card_node_insert_tail(exploding_djanni_cards, tmp_card); // adding the card in the relative deck
        printf("%d: %s\n", tmp_card.type, tmp_card.title); //todo:variadic
	}
	// redundant check in case we encountered EOF
	if (i != cardcount.n_exploding_djanni)
	{
		log_write("an error happened when finished to read the deck file (exploding djanni lines)");
        printf("%d != %d\n", i, cardcount.n_exploding_djanni); //todo:variadic
		return false;
	}

    // iter all the meooow cards
	for (i=0; !feof(fpDeck) && i < cardcount.n_meooow; i++)
	{
	    // scan type and title and exit in case of failure
        if (fscanf(fpDeck, "%u %31[^\n]s", &tmp_card.type, tmp_card.title)!=2)
        {
            log_write("an error happened when reading the deck file (meooow lines)");
            return false;
        }
		clear_file_input_line(fpDeck); // clear the remaining bytes of the line
        meooow_cards = card_node_insert_tail(meooow_cards, tmp_card);
        printf("%d: %s\n", tmp_card.type, tmp_card.title); //todo:variadic
	}
	// redundant check in case we encountered EOF
	if (i != cardcount.n_meooow)
	{
		log_write("an error happened when finished to read the deck file (meooow lines)");
        printf("%d != %d\n", i, cardcount.n_meooow); //todo:variadic
		return false;
	}

    // iter all the other cards
	for (i=0; !feof(fpDeck) && i < cardcount.n_other_cards; i++)
	{
	    // scan type and title and exit in case of failure
        if (fscanf(fpDeck, "%u %31[^\n]s", &tmp_card.type, tmp_card.title)==0)
        {
            log_write("an error happened when reading the deck file (other cards lines)");
            return false;
        }
		clear_file_input_line(fpDeck); // clear the remaining bytes of the line
        other_cards = card_node_insert_tail(other_cards, tmp_card); // adding the card in the relative deck
        printf("%d: %s\n", tmp_card.type, tmp_card.title); //todo:variadic
	}
	// redundant check in case we encountered EOF
	if (i != cardcount.n_other_cards)
	{
		log_write("an error happened when finished to read the deck file (other cards lines)");
        printf("%d != %d\n", i, cardcount.n_other_cards); //todo:variadic
		return false;
	}

	return true;
}

