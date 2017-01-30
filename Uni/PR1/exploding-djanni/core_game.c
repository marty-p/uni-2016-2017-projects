#include "core_game.h"

_Bool core_game_start(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL) // skip null ptr
	{
		log_write("the game has been started with a null environment...");
		return false;
	}

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
	{
		log_write("the game has been started with an out-of-range player's turn [player_turn %d, players_count %d]", pStatus->player_turn, players_count);
		return false;
	}

	// looping until we have a winner
	do
	{
		player_log_turn_data(&pPlayers[pStatus->player_turn], pStatus);
		// process the menu and returns false in case of problems (when saving)
		if (core_game_pause_menu(pPlayers, players_count, pDeck, pStatus)==false)
		{
			log_write("an error occurred in the core_game_pause_menu function...");
			return false;
		}
		// process the turn and returns false in case of problems
		if (core_game_process(pPlayers, players_count, pDeck, pStatus)==false)
		{
			log_write("an error occurred in the core_game_processing function...");
			return false;
		}
	}
	while (core_game_check_winners(pPlayers, players_count)==false);

	return true;
}

_Bool core_game_check_winners(const Player pPlayers[], int players_count)
{
	int alive_players = 0; // counts the alive players
	int i; // counter for iteration
	if (pPlayers!=NULL) // skip null ptr
	{
		for (i=0; i<players_count; i++) // iter all the players
		{
			if (pPlayers[i].is_alive==true) // increase if alive
				alive_players++;
		}
	}
	return (alive_players <= 1); // there's a winner only if 1 or less are alive
}

_Bool core_game_pause_menu(const Player pPlayers[], int players_count, const CardDeck * pDeck, const GameStatus * pStatus)
{
	char menu_choice;

	printf("What do you want to do? (any:continue, 1:save, 2:save&quit, q:quit)\n");
	printf("\t0. Continue\n");
	printf("\t1. Save the game\n");
	printf("\t2. Save and quit the game\n");
	printf("\tq. Quit the game without saving\n");

	// ask which choice to make
	scanf("%c", &menu_choice);
	clear_input_line(); // clear the input line from junk

	switch (menu_choice)
	{
		case '1':
			if (core_init_save_game(pPlayers, players_count, pDeck, pStatus)==false)
				return false;
			break;
		case '2':
			core_init_save_game(pPlayers, players_count, pDeck, pStatus);
			return false;
			break; // redundant line (not executed due to the return statement)
		case 'q':
			return false;
			break; // redundant line (not executed due to the return statement)
		case '0':
		default:
			break;
	}

	return true;
}

_Bool core_game_process(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	_Bool has_attacked = false; // variable to specify whether the player has attacked or not

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	if (pPlayers[pStatus->player_turn].type==AI && core_game_process_ai_player(pPlayers, players_count, pDeck, pStatus, &has_attacked)==false)
		return false;
	else if (pPlayers[pStatus->player_turn].type==REAL && core_game_process_real_player(pPlayers, players_count, pDeck, pStatus, &has_attacked)==false)
		return false;

	// get the next turn
	if (core_game_get_next_turn(pPlayers, players_count, pStatus, has_attacked)==false)
		return false;

	return true;
}

_Bool core_game_get_next_turn(const Player pPlayers[], int players_count, GameStatus * pStatus, _Bool has_attacked)
{
	if (pPlayers==NULL || pStatus==NULL) // skip null ptr
		return false;

	if (core_game_check_winners(pPlayers, players_count)==true) // we at least know that two are still alive
		return true;

	if (pStatus->is_attacked==false || has_attacked==true) // switch player's turn if not being attacked or has attacked others
	{
		// pick up a valid next turn
		do
		{
			pStatus->player_turn = (pStatus->player_turn + 1) % players_count; // rotate the turns if exceeds the max count
		}
		while (pPlayers[pStatus->player_turn].is_alive==false); // repeat if the next is dead
	}
	else // reset the is attacked flag repeating another turn
		pStatus->is_attacked = false;

	pStatus->total_turns++; // increase the total turns' counter
	return true;
}

_Bool core_game_process_ai_player(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, _Bool * has_attacked)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || has_attacked==NULL) // skip null ptr
		return false;

	// _Bool should_draw = true; // variable to specify whether the player should draw a card or not
	return true;
}

_Bool core_game_process_real_player(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, _Bool * has_attacked)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || has_attacked==NULL) // skip null ptr
		return false;

	// _Bool should_draw = true; // variable to specify whether the player should draw a card or not
	return true;
}

void core_game_choose_player_cards(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, _Bool * has_attacked)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || has_attacked==NULL) // skip null ptr
		return;
}

