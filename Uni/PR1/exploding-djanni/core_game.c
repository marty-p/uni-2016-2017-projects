#include "core_game.h"

_Bool core_game_start(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus)
{
	GameEnv game_env = {0}; // game environment (not stored in the .sav file)
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

	// looping until we have a winner (they could be all dead even before starting
	while (core_game_check_winners(pPlayers, players_count)==false)
	{
		clear_all_delayed(); // clear the console
		log_write("turn #%d is starting...", pStatus->total_turns);
		printf("Player #%d (%s)'s turn! (Turn #%d)\n", pStatus->player_turn+1, pPlayers[pStatus->player_turn].name, pStatus->total_turns);

		// process the menu and returns false in case of quitting
		if (core_game_pause_menu(pPlayers, players_count, pDeck, pStatus)==false)
			return false;
		// reset game_env
		game_env.has_drawn = false;
		game_env.is_noped = false;
		game_env.has_attacked = false;
		game_env.saw_terrible_future = false;
		game_env.selected_djanni_mode = DM_SINGLE;
		// process the turn and returns false in case of problems
		if (core_game_process(pPlayers, players_count, pDeck, pStatus, &game_env)==false)
			return false;
	}

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

void core_game_print_winners(const Player pPlayers[], int players_count)
{
	int i; // counter for iteration
	if (pPlayers!=NULL) // skip null ptr
	{
		for (i=0; i<players_count; i++) // iter all the players
		{
			if (pPlayers[i].is_alive==true) // increase if alive
			{
				printf("The player #%d (%s) has won!\n", i+1, pPlayers[i].name);
				log_write("the player #%d (%s) has won!", i+1, pPlayers[i].name);
			}
		}
	}
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
			log_write("saving...");
			if (core_init_save_game(pPlayers, players_count, pDeck, pStatus)==false)
			{
				log_write("an error occurred in the core_init_save_game function...");
				return false;
			}
			break;
		case '2':
			log_write("saving and quitting...");
			core_init_save_game(pPlayers, players_count, pDeck, pStatus);
			return false;
			break; // redundant line (not executed due to the return statement)
		case 'q':
			log_write("quitting...");
			return false;
			break; // redundant line (not executed due to the return statement)
		case '0':
		default:
			log_write("continuing...");
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

	// log deck count
	deck_log_print_count(pDeck);
	// log the turn data
	player_log_turn_data(&pPlayers[pStatus->player_turn], pStatus);

	// log exploding djanni pct draw
	if (pPlayers[pStatus->player_turn].type==REAL)
		printf("There are still %d %s in the deck! (%.2f%% to draw one in the remaining %d cards)\n", core_deck_count_of_type_n(pDeck, EXPLODING_DJANNI), get_card_type_name(EXPLODING_DJANNI), core_deck_get_pct_of_type_n(pDeck, EXPLODING_DJANNI), pDeck->count);
	log_write("there are still %d %s in the deck! (%.2f%% to draw one in the remaining %d cards)", core_deck_count_of_type_n(pDeck, EXPLODING_DJANNI), get_card_type_name(EXPLODING_DJANNI), core_deck_get_pct_of_type_n(pDeck, EXPLODING_DJANNI), pDeck->count);

	// check if attacked
	if (pStatus->is_attacked==true)
	{
		if (pPlayers[pStatus->player_turn].type==REAL)
			printf("You are under attack! Use an attack card or repeat the turn twice!\n");
		else if (pPlayers[pStatus->player_turn].type==AI)
			printf("Player #%d (%s) under attack!\n", pStatus->player_turn+1, pPlayers[pStatus->player_turn].name);
		log_write("player #%d (%s) is under attack...", pStatus->player_turn+1, pPlayers[pStatus->player_turn].name);
	}

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

	if (pStatus->is_attacked==false) // switch player's turn if not being attacked or has attacked others
	{
		// pick up a valid next turn
		do
		{
			pStatus->player_turn = (pStatus->player_turn + 1) % players_count; // rotate the turns if exceeds the max count
		}
		while (pPlayers[pStatus->player_turn].is_alive==false); // repeat if the next is dead
		// set the attack flag for the next turn
		if (pEnv->has_attacked==true)
		{
			pEnv->has_attacked = false;
			pStatus->is_attacked = true;
		}
	}
	else // reset the is attacked flag repeating another turn
		pStatus->is_attacked = false;

	pStatus->total_turns++; // increase the total turns' counter
	return true;
}

_Bool core_game_process_real_player(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (core_game_continue_menu(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
		return false;

	return true;
}

_Bool core_game_continue_menu(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	char menu_choice;
	_Bool wrong_choice;

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	do
	{
		log_write("displaying the continue menu...");
		printf("Count of the players' cards:\n");
		player_print_all_card_counts(pPlayers, players_count);
		printf("List of your current cards:\n");
		player_print_hand(&pPlayers[pStatus->player_turn]);

		player_log_turn_data(&pPlayers[pStatus->player_turn], pStatus);
		printf("What do you want to do? (1:draw a card, 2:use a card, q:quit)\n");
		if (pEnv->has_drawn==false)
			printf("\t1. Draw a card\n");
		if (pPlayers[pStatus->player_turn].card_count > 0)
			printf("\t2. Use a card\n");
		printf("\t3. Save the game\n");
		printf("\tq. Quit the game\n");

		// ask which choice to make
		scanf("%c", &menu_choice);
		clear_input_line(); // clear the input line from junk

		wrong_choice = false;
		switch (menu_choice)
		{
			case '1':
				if (pEnv->has_drawn==true)
				{
					wrong_choice = true;
					break;
				}
				log_write("drawing...");
				if (core_game_card_draw(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
				{
					log_write("an error occurred in the core_game_card_draw function...");
					return false;
				}
				pEnv->has_drawn = true;
				break;
			case '2':
				log_write("using a card...");
				if (pPlayers[pStatus->player_turn].card_count <= 0)
				{
					printf("You have no more cards.\n");
					wrong_choice = true;
					break;
				}
				if (core_game_real_card_use(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
					return false;
				break;
			case '3':
				log_write("saving...");
				if (core_init_save_game(pPlayers, players_count, pDeck, pStatus)==false)
				{
					log_write("an error occurred in the core_init_save_game function...");
					return false;
				}
				break;
			case 'q':
				log_write("quitting...");
				return false;
				break; // redundant line (not executed due to the return statement)
			default:
				wrong_choice = true;
				break;
		}
	}
	while (wrong_choice==true || pEnv->has_drawn==false); // repeat in case of wrong answer

	return true;
}

_Bool core_game_card_draw(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (pDeck->card_list==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	log_write("Player #%d (%s) drew the card... [%d]%s: %s",
		pStatus->player_turn+1, pPlayers[pStatus->player_turn].name, pDeck->card_list->card.type, get_card_type_name(pDeck->card_list->card.type), pDeck->card_list->card.title
	);
	if (pPlayers[pStatus->player_turn].type==REAL || pDeck->card_list->card.type==EXPLODING_DJANNI) // only exploding djanni will be shown for ai players
		printf("You drew the card [%d]%s: %s!\n", pDeck->card_list->card.type, get_card_type_name(pDeck->card_list->card.type), pDeck->card_list->card.title);
	else if (pPlayers[pStatus->player_turn].type==AI)
		printf("Player #%d (%s) drew a card!\n", pStatus->player_turn+1, pPlayers[pStatus->player_turn].name);

	if (pDeck->card_list->card.type==EXPLODING_DJANNI) // check if the first deck card is an exploding djanni
	{
		if (core_player_has_in(&pPlayers[pStatus->player_turn], MEOOOW)==false) // check if the player doesn't have a meooow
		{
			core_remove_deck_head(pDeck); // remove the exploding djanni from the deck
			pPlayers[pStatus->player_turn].is_alive=false; // set the player as dead
			pStatus->is_attacked=false; // already dead
			printf("You exploded into smithereens and died.\n");
			log_write("player #%d (%s) is out of the game...", pStatus->player_turn+1, pPlayers[pStatus->player_turn].name);
			return true;
		}
		// a meooow card will be used to not die
		core_shuffle_deck_head(pDeck); // shuffle the exploding djanni randomly in the deck
		core_remove_player_card_type(&pPlayers[pStatus->player_turn], MEOOOW); // remove the meooow card from the player
		printf("You used a meooow card and got saved.\n");
		log_write("player #%d (%s) used a meoow card and the exploding djanni has been shuffled again in the deck...", pStatus->player_turn+1, pPlayers[pStatus->player_turn].name);
		return true;
	}

	core_player_draw_from_deck(&pPlayers[pStatus->player_turn], pDeck); // draw a card

	return true;
}

_Bool core_game_real_card_use(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	int selected_card;
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (core_game_real_choose_player_card(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, &selected_card)==false)
		return false;
	if (core_game_process_player_card(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
		return false;

	return true;
}

_Bool core_game_card_can_nope(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int selected_card)
{
	int i;
	char get_choice;
	_Bool is_nope_reused;
#ifdef CLEAR_CONSOLE_WHEN_NOPING
	_Bool is_console_clear = false;
#endif
	Card * used_card = NULL;
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	used_card = card_list_select_n(&pPlayers[player_index], selected_card);
	if (used_card==NULL) // have the player already lost that card?
		return false;

	log_write("checking if it can be noped by other players...");
	pEnv->is_noped = false;
	do
	{
		is_nope_reused = false;
		for (i=0; i<players_count; i++)
		{
			if (pPlayers[i].is_alive==false) // skip dead players
				continue;
			if (i==player_index && is_nope_reused==false) // skip yourself when "blocking", allowed when "unblocking"
				continue;
			if (core_player_has_in(&pPlayers[i], NOPE)==true)
			{
				if (pPlayers[i].type==REAL)
				{
#ifdef CLEAR_CONSOLE_WHEN_NOPING
					if (is_console_clear==false)
					{
						if (pPlayers[player_index].type==REAL) // no need to hide for ai players
						{
							clear_all_delayed(); // clear the console
							is_console_clear = true;
							printf("Player #%d (%s) used the card [%d]%s: %s\n", player_index+1, pPlayers[player_index].name, used_card->type, get_card_type_name(used_card->type), used_card->title);
							if (used_card->type==DJANNI_CARDS)
								printf("Player #%d (%s) has chosen the %s djanni mode!\n", player_index+1, pPlayers[player_index].name, get_djanni_mode_name(pEnv->selected_djanni_mode));
						}
					}
#endif
					if (pEnv->is_noped==false)
						printf("Player #%d (%s), do you want to use a %s card to block Player #%d (%s)'s %s? (y:yes, any:no)\n",
								i+1, pPlayers[i].name, get_card_type_name(NOPE), player_index+1, pPlayers[player_index].name, get_card_type_name(used_card->type)
						);
					else
						printf("Player #%d (%s), do you want to use a %s card to unblock Player #%d (%s)'s %s? (y:yes, any:no)\n",
								i+1, pPlayers[i].name, get_card_type_name(NOPE), player_index+1, pPlayers[player_index].name, get_card_type_name(used_card->type)
						);
					scanf("%c", &get_choice);
					clear_input_line(); // clear the input line from junk
					if (get_choice!='y') // if it's not yes
						continue;
					pEnv->is_noped = !pEnv->is_noped;
					is_nope_reused = true;
					core_remove_player_card_type(&pPlayers[i], NOPE);
					log_write("player #%d (%s) used a %s card to block Player #%d (%s)'s %s",
							i+1, pPlayers[i].name, get_card_type_name(NOPE), player_index+1, pPlayers[player_index].name, get_card_type_name(used_card->type)
					);
				}
				else if (pPlayers[i].type==AI)
				{
					// consider ATTACK the most
					if (core_game_am_i_next(pPlayers, players_count, i, pStatus, pEnv, used_card->type==ATTACK)==true && core_game_ai_is_it_valuable_card_to_nope(pPlayers, players_count, i, used_card, pEnv)==true)
					{
						pEnv->is_noped = !pEnv->is_noped;
						is_nope_reused = true;
						core_remove_player_card_type(&pPlayers[i], NOPE);
						log_write("player #%d (%s) used a %s card to %s Player #%d (%s)'s %s",
								i+1, pPlayers[i].name, get_card_type_name(NOPE), (pEnv->is_noped==true) ? "block" : "unblock", player_index+1, pPlayers[player_index].name, get_card_type_name(used_card->type)
						);
						printf("Player #%d (%s) used a %s card to %s Player #%d (%s)'s %s\n",
								i+1, pPlayers[i].name, get_card_type_name(NOPE), (pEnv->is_noped==true) ? "block" : "unblock", player_index+1, pPlayers[player_index].name, get_card_type_name(used_card->type)
						);
					}
				}
			}
		}
	}
	while (is_nope_reused==true); // repeat the loop in case someone uses a nope

#ifdef CLEAR_CONSOLE_WHEN_NOPING
	if (pPlayers[player_index].type==REAL && is_console_clear==true) // no need to hide for ai players
	{
		printf("We're going to switch to Player #%d (%s)!\n", player_index+1, pPlayers[player_index].name);
		clear_all();
	}
#endif

	return pEnv->is_noped;
}

_Bool core_game_card_use_see_the_future(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	log_write("player #%d (%s) is going to see the future...", player_index+1, pPlayers[player_index].name);
	if (pPlayers[player_index].type==REAL)
	{
		printf("You're going to see the future:\n");
		deck_print_first_n_cards(pDeck, SEE_THE_FUTURE_FORESEE_NUM);
		deck_log_print_first_n_cards(pDeck, SEE_THE_FUTURE_FORESEE_NUM);
	}
	else if (pPlayers[player_index].type==AI)
	{
		if (pDeck->card_list!=NULL && pDeck->card_list->card.type==EXPLODING_DJANNI)
			pEnv->saw_terrible_future = true;
		deck_log_print_first_n_cards(pDeck, SEE_THE_FUTURE_FORESEE_NUM);
	}
	return true;
}

_Bool core_game_card_use_favor(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int selected_card)
{
	int selected_player_index = 0;
	int selected_player_card = 0;
	Card * used_card = NULL;
	int i;

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	if (core_game_check_winners(pPlayers, players_count)==true) // we at least know that two are still alive
		return false;

	log_write("player #%d (%s) is going to ask for a favor...", player_index+1, pPlayers[player_index].name);

	if (pPlayers[player_index].type==REAL)
	{
		do // repeat if out-of-range or yourself or dead players
		{
			printf("Choose the player which you want to ask for a favor: (0-%d)\n", players_count-1);
			for (i=0; i<players_count; i++)
			{
				if (i!=player_index && pPlayers[i].is_alive==true)
				{
					printf("(%d) Player #%d (%s)", i, i+1, pPlayers[i].name);
					if (pPlayers[i].card_count <= 0) // check if empty-handed
						printf(" (empty-handed)");
					printf("\n");
				}
			}
			scanf("%d", &selected_player_index);
			clear_input_line(); // clear the input line from junk
		}
		while (selected_player_index<0 || selected_player_index>=players_count || selected_player_index==player_index || pPlayers[selected_player_index].is_alive==false);
	}
	else if (pPlayers[player_index].type==AI)
	{
		if (core_game_check_winners(pPlayers, players_count)==true) // we at least know that two are still alive
			return false;

		selected_player_index = 0;
		do
		{
			selected_player_index = get_random_number(0, players_count-1);
		}
		while (pPlayers[selected_player_index].is_alive==false || selected_player_index==player_index || selected_player_index>=players_count); // repeat if dead, itself or out-of-range
	}

	// skip empty-handed players (the card will be consumed anyway)
	if (pPlayers[selected_player_index].card_count <= 0)
	{
		printf("The Player #%d (%s) has no more cards.\n", selected_player_index+1, pPlayers[selected_player_index].name);
		return false;
	}

	log_write("switching interaction to player #%d (%s)...", selected_player_index+1, pPlayers[selected_player_index].name);
	if (pPlayers[selected_player_index].type==REAL)
	{
		clear_all_delayed(); // clear the console
		// double warning to give enough time
		printf("We're going to switch to Player #%d (%s)!\n", selected_player_index+1, pPlayers[selected_player_index].name);
		clear_all();
	}

	if (pPlayers[selected_player_index].type==REAL)
	{
		printf("Player #%d (%s), which card do you want to give?\n", selected_player_index+1, pPlayers[selected_player_index].name);
		if (core_game_real_choose_player_card(pPlayers, players_count, selected_player_index, pDeck, pStatus, pEnv, &selected_player_card)==false)
			return false;
	}
	else if (pPlayers[selected_player_index].type==AI)
	{
		if (core_game_ai_pickup_worst_card(&pPlayers[selected_player_index], &selected_player_card)==false)
			return false;
	}

	used_card = card_list_select_n(&pPlayers[selected_player_index], selected_player_card);
	if (used_card==NULL) // have the player already lost that card?
		return false;

	log_write("player #%d (%s) received from player #%d (%s) the card [%d]%s (%s)",
			player_index+1, pPlayers[player_index].name,
			selected_player_index+1, pPlayers[selected_player_index].name,
			used_card->type, get_card_type_name(used_card->type), used_card->title
	);
	if (pPlayers[selected_player_index].type==REAL)
		printf("You gave the following card to Player #%d (%s): [%d]%s (%s)\n", player_index+1, pPlayers[player_index].name, used_card->type, get_card_type_name(used_card->type), used_card->title);

	log_write("switching interaction to player #%d (%s)...", player_index+1, pPlayers[player_index].name);
	if (pPlayers[selected_player_index].type==REAL)
	{
		clear_all_delayed(); // clear the console
		// double warning to give enough time
		printf("We're going to switch to Player #%d (%s)!\n", player_index+1, pPlayers[player_index].name);
		clear_all();
	}

	core_remove_player_n_card(&pPlayers[player_index], selected_card); // internal delete
	printf("You received the following card from Player #%d (%s): [%d]%s (%s)\n",
			selected_player_index+1, pPlayers[selected_player_index].name,
			used_card->type, get_card_type_name(used_card->type), used_card->title
	);
	core_player_give_card_n_to_player(&pPlayers[selected_player_index], &pPlayers[player_index], selected_player_card); // after this, used_card will become a dangling ptr
	used_card = NULL;

	return true;
}

_Bool core_game_card_use_djanni_cards(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int selected_card)
{
	_Bool can_couple = false;
	_Bool can_triple = false;
	DjanniMode chosen_mode = DM_SINGLE;
	const Card * used_card = NULL; // used card ptr
	Card copy_card = {{0}}; // copy of used card
	int i;
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	can_couple = core_game_card_can_use_djanni_cards_couple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card);
	can_triple = core_game_card_can_use_djanni_cards_triple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card);

	log_write("player #%d (%s) is going to select a djanni card mode...", player_index+1, pPlayers[player_index].name);
	if (can_couple==true || can_triple==true)
	{
		if (pPlayers[player_index].type==REAL)
		{
			do
			{
				log_write("In which mode do you want to use the djanni cards?");
				printf("%u. %s Mode\n", DM_SINGLE, get_djanni_mode_name(DM_SINGLE));
				if (can_couple==true)
					printf("%u. %s Mode\n", DM_COUPLE, get_djanni_mode_name(DM_COUPLE));
				if (can_triple==true)
					printf("%u. %s Mode\n", DM_TRIPLE, get_djanni_mode_name(DM_TRIPLE));
				scanf("%u", &chosen_mode);
				clear_input_line(); // clear the input line from junk
			}
			while (chosen_mode>=DJANNI_MODE_NUM || (chosen_mode==DM_COUPLE && can_couple==false) || (chosen_mode==DM_TRIPLE && can_triple==false)); // note: it's unsigned
		}
		else if (pPlayers[player_index].type==AI)
		{
			chosen_mode = DM_SINGLE;
			switch (pEnv->selected_djanni_mode) // specified elsewhere
			{
				case DM_COUPLE:
					if (can_couple==true)
						chosen_mode = DM_COUPLE;
					break;
				case DM_TRIPLE:
					if (can_triple==true)
						chosen_mode = DM_TRIPLE;
					break;
				case DM_SINGLE:
				default:
					break;
			}
		}
	}
	else // if only the single mode is available, no need to ask
		chosen_mode = DM_SINGLE;

	log_write("player #%d (%s) chose the %s djanni card mode...", player_index+1, pPlayers[player_index].name, get_djanni_mode_name(chosen_mode));
	printf("You have chosen the %s djanni mode!\n", get_djanni_mode_name(chosen_mode));
	pEnv->selected_djanni_mode = chosen_mode;
	if (core_game_card_can_nope(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==true)
	{
		// select that djanni card
		used_card = card_list_const_select_n(&pPlayers[player_index], selected_card);
		if (used_card==NULL) // have the player already lost that card?
			return false;
		copy_card = *used_card;

		// delete the djanni cards
		switch (chosen_mode)
		{
			case DM_SINGLE:
				core_remove_player_first_matched_card(&pPlayers[player_index], copy_card); // delete the used card
				break;
			case DM_COUPLE:
				for (i=0; i<=DJANNI_DOUBLE_MATCH_NUM; i++) // iter n match+1
					core_remove_player_first_matched_card(&pPlayers[player_index], copy_card); // delete the used card
				break;
			case DM_TRIPLE:
				for (i=0; i<=DJANNI_TRIPLE_MATCH_NUM; i++) // iter n match+1
					core_remove_player_first_matched_card(&pPlayers[player_index], copy_card); // delete the used card
				break;
		}
		used_card = NULL; // fix dangling ptr
		return true;
	}

	// process the mode
	switch (chosen_mode)
	{
		case DM_SINGLE:
			return false; // it will be removed externally since we did nothing
			break;
		case DM_COUPLE:
			if (core_game_card_use_djanni_cards_couple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
				return false;
			break;
		case DM_TRIPLE:
			if (core_game_card_use_djanni_cards_triple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
				return false;
			break;
	}

	return true;
}

_Bool core_game_card_use_djanni_cards_couple(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int selected_card)
{
	int selected_player_index = 0; // selected player which you take the card
	int selected_player_card = 0; // selected player card to pick up
	const Card * used_card = NULL; // used card ptr
	Card copy_card = {{0}}; // copy of used card
	int i=0; // for itering
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	if (core_game_card_can_use_djanni_cards_couple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false) // double check
		return false;

	used_card = card_list_const_select_n(&pPlayers[player_index], selected_card);
	if (used_card==NULL) // have the player already lost that card?
		return false;

	// delete the djanni cards
	copy_card = *used_card;
	for (i=0; i<=DJANNI_DOUBLE_MATCH_NUM; i++) // iter n match+1
		core_remove_player_first_matched_card(&pPlayers[player_index], copy_card); // delete the used card
	used_card = NULL; // fix dangling ptr

	// choose a card of the other players as hidden and take it
	log_write("player #%d (%s) is going to choose a player...", player_index+1, pPlayers[player_index].name);
	if (pPlayers[player_index].type==REAL)
	{
		do // repeat if out-of-range or yourself or dead players
		{
			printf("Choose the player from which you will pick up a card: (0-%d)\n", players_count-1);
			for (i=0; i<players_count; i++)
			{
				if (i!=player_index && pPlayers[i].is_alive==true)
				{
					printf("(%d) Player #%d (%s)", i, i+1, pPlayers[i].name);
					if (pPlayers[i].card_count <= 0) // check if empty-handed
						printf(" (empty-handed)");
					printf("\n");
				}
			}
			scanf("%d", &selected_player_index);
			clear_input_line(); // clear the input line from junk
		}
		while (selected_player_index<0 || selected_player_index>=players_count || selected_player_index==player_index || pPlayers[selected_player_index].is_alive==false);
	}
	else if (pPlayers[player_index].type==AI)
	{
		if (core_game_check_winners(pPlayers, players_count)==true) // we at least know that two are still alive
			return false;

		selected_player_index = 0;
		do
		{
			selected_player_index = get_random_number(0, players_count-1);
		}
		while (pPlayers[selected_player_index].is_alive==false || selected_player_index==player_index || selected_player_index>=players_count); // repeat if dead, itself or out-of-range
	}

	// skip empty-handed players (the card will be consumed anyway)
	if (pPlayers[selected_player_index].card_count <= 0)
	{
		printf("The Player #%d (%s) has no more cards.\n", selected_player_index+1, pPlayers[selected_player_index].name);
		return true;
	}

	if (pPlayers[player_index].type==REAL)
	{
		printf("Player #%d (%s), which card do you want to pick up?\n", player_index+1, pPlayers[player_index].name);
		if (core_game_real_choose_another_player_card(pPlayers, players_count, selected_player_index, pDeck, pStatus, pEnv, &selected_player_card, true)==false)
			return false;
	}
	else if (pPlayers[player_index].type==AI)
		selected_player_card = get_random_number(0, pPlayers[selected_player_index].card_count-1);

	used_card = card_list_select_n(&pPlayers[selected_player_index], selected_player_card);
	if (used_card==NULL) // have the player already lost that card?
		return false;

	log_write("player #%d (%s) picked up from player #%d (%s) the card [%d]%s (%s)",
			player_index+1, pPlayers[player_index].name,
			selected_player_index+1, pPlayers[selected_player_index].name,
			used_card->type, get_card_type_name(used_card->type), used_card->title
	);
	printf("You picked up the following card from Player #%d (%s): [%d]%s (%s)\n",
			selected_player_index+1, pPlayers[selected_player_index].name,
			used_card->type, get_card_type_name(used_card->type), used_card->title
	);

	core_player_give_card_n_to_player(&pPlayers[selected_player_index], &pPlayers[player_index], selected_player_card); // after this, used_card will become a dangling ptr
	used_card = NULL;

	return true;
}

_Bool core_game_card_use_djanni_cards_triple(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int selected_card)
{
	int selected_player_index = 0; // selected player which you take the card
	int selected_player_card = 0; // selected player card to pick up
	const Card * used_card = NULL; // used card ptr
	Card copy_card = {{0}}; // copy of used card
	int i=0; // for itering
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	if (core_game_card_can_use_djanni_cards_triple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false) // double check
		return false;

	used_card = card_list_const_select_n(&pPlayers[player_index], selected_card);
	if (used_card==NULL) // have the player already lost that card?
		return false;
	copy_card = *used_card;

	// delete the djanni cards
	for (i=0; i<=DJANNI_TRIPLE_MATCH_NUM; i++) // iter n match+1
		core_remove_player_first_matched_card(&pPlayers[player_index], copy_card); // delete the used card
	used_card = NULL; // fix dangling ptr

	// choose a card of the other players as hidden and take it
	log_write("player #%d (%s) is going to choose a player...", player_index+1, pPlayers[player_index].name);
	if (pPlayers[player_index].type==REAL)
	{
		do // repeat if out-of-range or yourself or dead players
		{
			printf("Choose the player from which you will pick up a card: (0-%d)\n", players_count-1);
			for (i=0; i<players_count; i++)
			{
				if (i!=player_index && pPlayers[i].is_alive==true)
				{
					printf("(%d) Player #%d (%s)", i, i+1, pPlayers[i].name);
					if (pPlayers[i].card_count <= 0) // check if empty-handed
						printf(" (empty-handed)");
					printf("\n");
				}
			}
			scanf("%d", &selected_player_index);
			clear_input_line(); // clear the input line from junk
		}
		while (selected_player_index<0 || selected_player_index>=players_count || selected_player_index==player_index || pPlayers[selected_player_index].is_alive==false);
	}
	else if (pPlayers[player_index].type==AI)
	{
		if (core_game_check_winners(pPlayers, players_count)==true) // we at least know that two are still alive
			return false;

		selected_player_index = 0;
		do
		{
			selected_player_index = get_random_number(0, players_count-1);
		}
		while (pPlayers[selected_player_index].is_alive==false || selected_player_index==player_index || selected_player_index>=players_count); // repeat if dead, itself or out-of-range
	}

	// skip empty-handed players (the card will be consumed anyway)
	if (pPlayers[selected_player_index].card_count <= 0)
	{
		printf("The Player #%d (%s) has no more cards.\n", selected_player_index+1, pPlayers[selected_player_index].name);
		return true;
	}

	if (pPlayers[player_index].type==REAL)
	{
		printf("Player #%d (%s), which card do you want to pick up?\n", player_index+1, pPlayers[player_index].name);
		if (core_game_real_choose_another_player_card(pPlayers, players_count, selected_player_index, pDeck, pStatus, pEnv, &selected_player_card, false)==false)
			return false;
	}
	else if (pPlayers[player_index].type==AI)
	{
		if (core_game_ai_pickup_best_card(&pPlayers[selected_player_index], &selected_player_card)==false)
			return false;
	}

	used_card = card_list_const_select_n(&pPlayers[selected_player_index], selected_player_card);
	if (used_card==NULL) // have the player already lost that card?
		return false;

	log_write("player #%d (%s) picked up from player #%d (%s) the card [%d]%s (%s)",
			player_index+1, pPlayers[player_index].name,
			selected_player_index+1, pPlayers[selected_player_index].name,
			used_card->type, get_card_type_name(used_card->type), used_card->title
	);
	printf("You picked up the following card from Player #%d (%s): [%d]%s (%s)\n",
			selected_player_index+1, pPlayers[selected_player_index].name,
			used_card->type, get_card_type_name(used_card->type), used_card->title
	);

	core_player_give_card_n_to_player(&pPlayers[selected_player_index], &pPlayers[player_index], selected_player_card); // after this, used_card will become a dangling ptr
	used_card = NULL;

	return true;
}

_Bool core_game_card_can_use_djanni_cards_couple(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv, int selected_card)
{
	const Card * used_card = NULL;
	int i;
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	used_card = card_list_const_select_n(&pPlayers[player_index], selected_card);
	if (used_card==NULL) // have the player already lost that card?
		return false;

	for (i=0; i<pPlayers[player_index].card_count; i++)
	{
		if (selected_card!=i && pPlayers[player_index].cards[i].type==DJANNI_CARDS) // skip itself
		{
			if (strcmp(used_card->title, pPlayers[player_index].cards[i].title) == 0) // true if they have same titles
				return true;
		}
	}

	return false;
}

_Bool core_game_card_can_use_djanni_cards_triple(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv, int selected_card)
{
	const Card * used_card = NULL;
	int i;
	int match_count = 0;
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	used_card = card_list_const_select_n(&pPlayers[player_index], selected_card);
	if (used_card==NULL) // have the player already lost that card?
		return false;

	for (i=0; i<pPlayers[player_index].card_count && match_count<DJANNI_TRIPLE_MATCH_NUM; i++)
	{
		if (selected_card!=i && pPlayers[player_index].cards[i].type==DJANNI_CARDS) // skip itself
		{
			if (strcmp(used_card->title, pPlayers[player_index].cards[i].title) == 0) // increase if they have same titles
				match_count++;
		}
	}

	return match_count>=DJANNI_TRIPLE_MATCH_NUM;
}

_Bool core_game_process_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int selected_card)
{
	const Card * used_card = NULL;
	_Bool internal_delete = false; // in case the processed card has been deleted inside another block (favor/djanni cards)
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	used_card = card_list_const_select_n(&pPlayers[player_index], selected_card);
	if (used_card==NULL) // have the player already lost that card?
		return false;

	printf("Player #%d (%s) used the card [%d]%s: %s\n",
			player_index+1, pPlayers[player_index].name, used_card->type, get_card_type_name(used_card->type), used_card->title
	);
	log_write("processing player #%d (%s)'s card [%d]%s: %s",
			player_index+1, pPlayers[player_index].name, used_card->type, get_card_type_name(used_card->type), used_card->title
	);
	switch (used_card->type)
	{
		// with no meaning
		case EXPLODING_DJANNI: // it should be impossible to "draw" and use it though
		case MEOOOW: // used only when an exploding djanni is drawn
		case NOPE: // it should be used only to "dispel" other cards
			break;
		case SHUFFLE: // shuffle the deck
			if (core_game_card_can_nope(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
			{
				core_shuffle_deck(pDeck);
				printf("The deck has been shuffled.\n");
			}
			break;
		case SEE_THE_FUTURE:
			if (core_game_card_can_nope(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
				core_game_card_use_see_the_future(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv);
			break;
		case ATTACK: // attack and skip the draw phase
			if (core_game_card_can_nope(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
			{
				pStatus->is_attacked = false;
				pEnv->has_attacked = true;
				pEnv->has_drawn = true;
				if (pPlayers[player_index].type==REAL)
					printf("You have declared an attack!\n");
				log_write("player #%d (%s) has declared an attack...", player_index+1, pPlayers[player_index].name);
			}
			break;
		case SKIP: // skip the draw phase
			if (core_game_card_can_nope(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
				pEnv->has_drawn = true;
			break;
		case FAVOR: // ask to another player a card (chosen by the other player)
			if (core_game_card_can_nope(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
				internal_delete = core_game_card_use_favor(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card);
			break;
		case DJANNI_CARDS: // it has 3 modes... single which does nothing, couple if two same djanni cards are used, and triple if three same djanni cards are used
			// nope check inside the function
			internal_delete = core_game_card_use_djanni_cards(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card);
			break;
	}

	// remove the card from the player's deck
	if (internal_delete==false) // skip if already deleted elsewhere
		core_remove_player_n_card(&pPlayers[player_index], selected_card);

	return true;
}

_Bool core_game_real_choose_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL || selected_card==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	if (pPlayers[player_index].card_count <= 0)
	{
		printf("You have no more cards.\n");
		log_write("player #%d (%s) has no more cards to select.", player_index+1, pPlayers[player_index].name);
		return false;
	}

	do
	{
		printf("List of your current cards:\n");
		player_print_hand(&pPlayers[player_index]);
		printf("Choose one of them: (0-%d)\n", pPlayers[player_index].card_count-1);
		scanf("%d", selected_card);
		clear_input_line(); // clear the input line from junk
	} while (*selected_card >= pPlayers[player_index].card_count); // repeat if out-of-range

	printf("You selected the following card:\n");
	player_print_n_card(&pPlayers[player_index], *selected_card);
	log_write("player #%d (%s) has selected:", player_index+1, pPlayers[player_index].name);
	player_log_print_n_card(&pPlayers[player_index], *selected_card);

	return true;
}

_Bool core_game_real_choose_another_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card, _Bool is_secret)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL || selected_card==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	if (pPlayers[player_index].card_count <= 0)
	{
		printf("The player #%d (%s) has no more cards.\n", player_index+1, pPlayers[player_index].name);
		log_write("player #%d (%s) has no more cards to pick up.", player_index+1, pPlayers[player_index].name);
		return false;
	}

	do
	{
		printf("List of player #%d (%s)'s current cards:\n", player_index+1, pPlayers[player_index].name);
		if (is_secret==true)
			player_print_secret_hand(&pPlayers[player_index]);
		else
			player_print_hand(&pPlayers[player_index]);
		printf("Choose one of them: (0-%d)\n", pPlayers[player_index].card_count-1);
		scanf("%d", selected_card);
		clear_input_line(); // clear the input line from junk
	} while (*selected_card >= pPlayers[player_index].card_count); // repeat if out-of-range

	printf("You selected the following card:\n");
	player_print_n_card(&pPlayers[player_index], *selected_card);
	log_write("player #%d (%s) has selected the following card from player #%d (%s):", pStatus->player_turn+1, pPlayers[pStatus->player_turn].name, player_index+1, pPlayers[player_index].name);
	player_log_print_n_card(&pPlayers[player_index], *selected_card);

	return true;
}

