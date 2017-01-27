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

	return true;
}

