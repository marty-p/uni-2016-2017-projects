#include "core_game.h"

_Bool core_game_start(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	GameEnv game_env = {0};
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
		// process the menu and returns false in case of quitting
		if (core_game_pause_menu(pPlayers, players_count, pDeck, pStatus)==false)
			return false;
		// todo: reset game_env
		// process the turn and returns false in case of problems
		if (core_game_process(pPlayers, players_count, pDeck, pStatus, &game_env)==false)
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
			{
				log_write("an error occurred in the core_init_save_game function...");
				return false;
			}
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

_Bool core_game_process(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	if (pPlayers[pStatus->player_turn].type==AI && core_game_process_ai_player(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
		return false;
	else if (pPlayers[pStatus->player_turn].type==REAL && core_game_process_real_player(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
		return false;

	// get the next turn
	if (core_game_get_next_turn(pPlayers, players_count, pStatus, pEnv)==false)
		return false;

	return true;
}

_Bool core_game_get_next_turn(const Player pPlayers[], int players_count, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (core_game_check_winners(pPlayers, players_count)==true) // we at least know that two are still alive
		return true;

	if (pStatus->is_attacked==false || pEnv->has_attacked==true) // switch player's turn if not being attacked or has attacked others
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

_Bool core_game_process_ai_player(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// _Bool should_draw = true; // variable to specify whether the player should draw a card or not
	return true;
}

_Bool core_game_process_real_player(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (core_game_continue_menu(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
		return false;

	// _Bool should_draw = true; // variable to specify whether the player should draw a card or not
	return true;
}

_Bool core_game_continue_menu(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	char menu_choice;
	_Bool wrong_choice;

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	do
	{
		printf("What do you want to do? (0:draw a card, 1:use a card, q:quit)\n");
		printf("\t1. Draw a card\n");
		printf("\t2. Use a card\n");
		printf("\tq. Quit the game\n");

		// ask which choice to make
		scanf("%c", &menu_choice);
		clear_input_line(); // clear the input line from junk

		switch (menu_choice)
		{
			case '1':
				if (core_game_card_draw(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
				{
					log_write("an error occurred in the core_game_card_draw function...");
					return false;
				}
				break;
			case '2':
				if (core_game_card_use(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
				{
					log_write("an error occurred in the core_game_card_use function...");
					return false;
				}
				break;
			case 'q':
				break;
			default:
				wrong_choice = true;
				break;
		}
	}
	while (wrong_choice==true); // repeat in case of wrong answer

	return true;
}

_Bool core_game_card_draw(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	return true;
}

_Bool core_game_card_use(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	int selected_card;
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (pPlayers[pStatus->player_turn].type==REAL)
	{
		if (core_game_real_choose_player_card(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, &selected_card)==false)
			return false;
		//todo
	}
	else
	{
		core_game_ai_choose_player_card(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, &selected_card);
	}
	return true;
}

_Bool core_game_real_choose_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL || selected_card==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	do
	{
		printf("List of the current cards: (0-%d)\n", pPlayers[pStatus->player_turn].card_count-1);
		player_print_hand(&pPlayers[player_index]);
		printf("Choose one of them:\n");
		scanf("%d", selected_card);
		clear_input_line(); // clear the input line from junk
	} while (*selected_card >= pPlayers[player_index].card_count); // repeat if out-of-range

	printf("you chose the following card:\n");
	player_print_n_card(&pPlayers[player_index], *selected_card);

	return true;
}

_Bool core_game_ai_choose_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL || selected_card==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	core_game_ai_pickup_best_card(&pPlayers[player_index], selected_card);

	printf("you chose the following card:\n");
	player_print_n_card(&pPlayers[player_index], *selected_card);

	return true;
}

_Bool core_game_ai_pickup_best_card(const Player * pPlayer, int * selected_card)
{
	static const CardType wish_list[CARD_TYPE_NUM] = {
		MEOOOW, //1
		NOPE, //3
		ATTACK, //5
		SKIP, //6
		SHUFFLE, //2
		SEE_THE_FUTURE, //4
		FAVOR, //7
		DJANNI_CARDS //8
	};
	CardNode * tmp;
	int count;
	_Bool chosen_card = false;
	int i;
	if (pPlayer==NULL || pPlayer->card_count<=0) // skip null ptr or cards<=0
		return false;

	for (i=0; i<CARD_TYPE_NUM && chosen_card==false; i++)
	{
		tmp = pPlayer->card_list;
		count = 0;
		while (tmp!=NULL && count<=pPlayer->card_count && chosen_card==false) // skip null ptr
		{
			if (wish_list[i]==tmp->card.type)
			{
				chosen_card = true;
				*selected_card = i;
			}
			tmp = tmp->next;
			count++;
		}
	}
	return chosen_card;
}

