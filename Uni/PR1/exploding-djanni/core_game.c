#include "core_game.h"

_Bool core_game_start(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	if (core_game_pause_menu(pPlayers, players_count, pDeck, pStatus)==false)
		return false;
	return true;
}

_Bool core_game_pause_menu(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	int menu_choice;

	printf("What do you want to do? (any:continue, 1:save, 2:save&quit, 3:quit)\n");
	printf("\t0. Continue\n");
	printf("\t1. Save the game\n");
	printf("\t2. Save and quit the game\n");
	printf("\t3. Quit the game without saving\n");

	// ask which choice to make
	scanf("%d", &menu_choice);
	clear_input_line(); // clear the input line from junk

	switch (menu_choice)
	{
		case 1:
			if (core_init_save_game(pPlayers, players_count, pDeck, pStatus)==false)
				return false;
			break;
		case 2:
			core_init_save_game(pPlayers, players_count, pDeck, pStatus);
			return false;
			break;
		case 3:
			return false;
			break;
		case 0:
		default:
			break;
	}

	return true;
}

