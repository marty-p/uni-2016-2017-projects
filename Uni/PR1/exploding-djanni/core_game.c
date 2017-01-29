#include "core_game.h"

_Bool core_game_start(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL) // skip null ptr
	{
		log_write("the game has been started with a null environment...");
		return false;
	}

	do
	{
		if (core_game_pause_menu(pPlayers, players_count, pDeck, pStatus)==false)
			return false;
	}
	while (core_game_check_winners(pPlayers, players_count)==false);

	return true;
}

_Bool core_game_check_winners(const Player pPlayers[], int players_count)
{
	int alive_players = 0; // counts the alive players
	int i; // counter for iteration
	if (pPlayers!=NULL)
	{
		for (i=0; i<players_count; i++)
		{
			if (pPlayers[i].is_alive==true)
				alive_players++;
		}
	}
	return (alive_players <= 1); // there's a winner only if there's 1 alive
}

_Bool core_game_pause_menu(const Player pPlayers[], int players_count, const CardDeck * pDeck, const GameStatus * pStatus)
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
			break; // redundant line (not executed due to the return statement)
		case 3:
			return false;
			break; // redundant line (not executed due to the return statement)
		case 0:
		default:
			break;
	}

	return true;
}

