#include "core_ai.h"

_Bool core_game_ai_next_draw_means_death(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv)
{
	double expdjanni_pct;
	_Bool has_meooow;

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	if (pPlayers[player_index].card_count<=0) // if no cards are available
		return false;

	if (pEnv->saw_terrible_future==true)
		return true;

	expdjanni_pct = core_deck_get_pct_of_type_n(pDeck, EXPLODING_DJANNI); // returns pct of drawing the exploding djanni card
	has_meooow = core_player_count_of_type_n(&pPlayers[pStatus->player_turn], MEOOOW) >= 1; // true if the player has at least 1 meooow

	if (has_meooow==false)
		return expdjanni_pct >= AI_PANIC_PCT; // 100%

	return false;
}

_Bool core_game_ai_is_in_panic(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	// check out-of-range issue
	if (player_index >= players_count)
		return false;

	if (pPlayers[player_index].card_count<=0) // if no cards are available
		return false;

	// check if there are usable cards
	if (core_game_ai_select_first_save_life_card(pPlayers, players_count, pDeck, pStatus, pEnv, NULL)==false
		&& core_game_ai_select_first_normal_card(pPlayers, players_count, pDeck, pStatus, pEnv, NULL)==false)
		return false;

	return core_game_ai_next_draw_means_death(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv);
}

_Bool core_game_ai_is_worried(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv)
{
	double lazy_pct;
	double expdjanni_pct;
	_Bool has_meooow;

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	// check out-of-range issue
	if (player_index >= players_count)
		return false;

	if (pPlayers[player_index].card_count<=0) // if no cards are available
		return false;

	lazy_pct = get_random_number(PCT_MIN, PCT_MAX);
	if (lazy_pct < AI_WORRIED_BUT_LAZY_PCT)
		return false; // 30% of getting lazy and doing nothing

	expdjanni_pct = core_deck_get_pct_of_type_n(pDeck, EXPLODING_DJANNI); // returns pct of drawing the exploding djanni card
	has_meooow = core_player_count_of_type_n(&pPlayers[pStatus->player_turn], MEOOOW) >= 1; // true if the player has at least 1 meooow

	if (has_meooow==false) // very simple check to be in panic
		return expdjanni_pct >= AI_WORRIED_PCT; // 10%

	return false;
}

_Bool core_game_ai_getting_lazy(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, GameEnv * pEnv)
{
	double lazy_pct;

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	// check out-of-range issue
	if (player_index >= players_count)
		return false;

	if (pPlayers[player_index].card_count<=0) // if no cards, just lazy by default
		return true;

	if (core_game_ai_is_in_panic(pPlayers, players_count, player_index, pDeck, pStatus, pEnv)==true) // can't be lazy if in panic
		return false;

	lazy_pct = get_random_number(PCT_MIN, PCT_MAX);
	return lazy_pct < AI_LAZY_PCT; // 15% of getting lazy and doing nothing if all is normal
}

_Bool core_game_process_ai_player(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	if (core_game_ai_continue(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
		return false;

	return true;
}

_Bool core_game_ai_continue(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	int selected_card;

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	// set a death flag (it will be set to false after some operations)
	pEnv->saw_terrible_future = core_game_ai_next_draw_means_death(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv);

	do // repeat until draw
	{
#ifdef SHOW_AI_DEBUG_INFO
		player_print_all_card_counts(pPlayers, players_count);
		player_print_hand(&pPlayers[pStatus->player_turn]);
		printf("couple %d, triple %d\n",
			core_game_ai_can_djanni_couple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, NULL),
			core_game_ai_can_djanni_triple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, NULL)
		);
#endif
		log_write("elaborating ai continue...");
		player_log_turn_data(&pPlayers[pStatus->player_turn], pStatus);

		// is ai under attack? then re-attack!
		if (pStatus->is_attacked==true)
		{
			log_write("core_game_ai re-attack...");
			if (card_list_find_first_type_n(&pPlayers[pStatus->player_turn], ATTACK, &selected_card)==true)
			{
				if (core_game_process_player_card(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
					return false;
			}
		} // not else... otherwise infinite loop

		// ai becomes lazy if not in panic and gets 15% or just empty-handed
		if (core_game_ai_getting_lazy(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv)==true) // ai draws a card and finish the turn
		{
			log_write("core_game_ai_getting_lazy...");
			if (core_game_ai_draw_card(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
				return false;
		}
		// ai in panic if it saw a terrible future (starting turn with a death flag: foresaw that the next card is the exploding djanni... or 100% to drop one)
		else if (core_game_ai_is_in_panic(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv)==true) // try to escape death in any way possible
		{
			log_write("core_game_ai_is_in_panic...");
			if (core_game_ai_select_first_save_life_card(pPlayers, players_count, pDeck, pStatus, pEnv, &selected_card)==true)
			{
				pEnv->saw_terrible_future = false;
				if (core_game_process_player_card(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
					return false;
			}
			else // nothing can erase that terrible future (ai is going to die pretty bad)
				pEnv->saw_terrible_future = false;
		}
		// ai gets worried if the exploding djanni gets 25% of possibility to drop and it has no meooow card
		else if (core_game_ai_is_worried(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv)==true) // try to play some cards to feel safe
		{
			log_write("core_game_ai_is_worried...");
			pEnv->saw_terrible_future = false; // this should be already as false at this point
			if (core_game_ai_select_first_normal_card(pPlayers, players_count, pDeck, pStatus, pEnv, &selected_card)==true)
			{
				if (core_game_process_player_card(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
					return false;
				// if nothing is wrong... draw a card
				if (pEnv->saw_terrible_future==false && get_random_number(PCT_MIN, PCT_MAX) <= AI_WORRIED_BUT_DRAW_ANYWAY_PCT) // if unknown future and 3%
					if (core_game_ai_draw_card(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
						return false;
			}
			else if (get_random_number(PCT_MIN, PCT_MAX) <= AI_MORE_WORRIED_PCT) // 70% of using a safelife card
			{
				if (core_game_ai_select_first_save_life_card(pPlayers, players_count, pDeck, pStatus, pEnv, &selected_card)==true)
				{
					if (core_game_process_player_card(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
						return false;
					if (pEnv->saw_terrible_future==false && get_random_number(PCT_MIN, PCT_MAX) <= AI_WORRIED_BUT_DRAW_ANYWAY_PCT) // if unknown future and 3%
						if (core_game_ai_draw_card(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
							return false;
				}
			}
		}
		else // normal play
		{
			log_write("core_game_ai_normal_play...");
			pEnv->saw_terrible_future = false; // this should be already as false at this point
			if (core_game_ai_select_first_trivial_card(pPlayers, players_count, pDeck, pStatus, pEnv, &selected_card)==true)
			{
				if (core_game_process_player_card(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
					return false;
				// if nothing is wrong... draw a card
				if (pEnv->saw_terrible_future==false)
					if (core_game_ai_draw_card(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
						return false;
			}
			// 10% of randomly using a safelife card
			else if (get_random_number(PCT_MIN, PCT_MAX) <= AI_LAZY_BUT_CRAZY_PCT && core_game_ai_select_first_save_life_card(pPlayers, players_count, pDeck, pStatus, pEnv, &selected_card)==true)
			{
				if (core_game_process_player_card(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==false)
					return false;
				if (pEnv->saw_terrible_future==false)
					if (core_game_ai_draw_card(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
						return false;
			}
			else if (core_game_ai_draw_card(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
				return false;
		}
	}
	while (pEnv->has_drawn==false);

	return true;
}

_Bool core_game_ai_draw_card(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	// check if already drawn
	if (pEnv->has_drawn==true)
		return true;

	if (core_game_card_draw(pPlayers, players_count, pDeck, pStatus, pEnv)==false) // draw a card
		return false;

	pEnv->has_drawn = true; // the turn will end after this
	return true;
}

_Bool core_game_ai_select_first_save_life_card(const Player pPlayers[], int players_count, const CardDeck * pDeck, const GameStatus * pStatus, GameEnv * pEnv, int * selected_card)
{
	static const CardType save_list[] = {
		ATTACK, //5
		SKIP, //6
		SHUFFLE, //2
		// SEE_THE_FUTURE, //4
		FAVOR, //7
		// DJANNI_CARDS //8
	};
	static const int save_len = sizeof(save_list)/sizeof(CardType);
	_Bool chosen_card = false;
	int i, j;

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	if (pPlayers[pStatus->player_turn].card_count<=0)
		return false;

	for (i=0; i<save_len && chosen_card==false; i++)
	{
		for (j=0; j<pPlayers[pStatus->player_turn].card_count && chosen_card==false; j++)
		{
			if (save_list[i]==pPlayers[pStatus->player_turn].cards[j].type)
			{
				chosen_card = true;
				if (selected_card!=NULL)
					*selected_card = j;
			}
		}
	}

	if (chosen_card==false) // if nothing has been found... then chose a djanni mode if available
	{
		if (core_game_ai_can_djanni_triple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==true)
		{
			pEnv->selected_djanni_mode = DM_TRIPLE;
			return true;
		}
		else if (core_game_ai_can_djanni_couple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==true)
		{
			pEnv->selected_djanni_mode = DM_COUPLE;
			return true;
		}
	}

	return chosen_card;
}

_Bool core_game_ai_select_first_trivial_card(const Player pPlayers[], int players_count, const CardDeck * pDeck, const GameStatus * pStatus, GameEnv * pEnv, int * selected_card)
{
	static const CardType trivial_list[] = {
		SEE_THE_FUTURE, //4
		FAVOR, //7
	};
	static const int trivial_len = sizeof(trivial_list)/sizeof(CardType);
	_Bool chosen_card = false;
	int i, j;

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	if (pPlayers[pStatus->player_turn].card_count<=0) // skip if empty
		return false;

	for (i=0; i<trivial_len && chosen_card==false; i++) // iter all the types and then all the player's cards
	{
		for (j=0; j<pPlayers[pStatus->player_turn].card_count && chosen_card==false; j++)
		{
			if (trivial_list[i]==pPlayers[pStatus->player_turn].cards[j].type)
			{
				chosen_card = true;
				if (selected_card!=NULL)
					*selected_card = j;
			}
		}
	}
	return chosen_card;
}

_Bool core_game_ai_select_first_normal_card(const Player pPlayers[], int players_count, const CardDeck * pDeck, const GameStatus * pStatus, GameEnv * pEnv, int * selected_card)
{
	static const CardType normal_list[] = {
		SHUFFLE, //2
		SEE_THE_FUTURE, //4
		FAVOR, //7
	};
	static const int normal_len = sizeof(normal_list)/sizeof(CardType);
	_Bool chosen_card = false;
	int i, j;

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	if (pPlayers[pStatus->player_turn].card_count<=0) // skip if empty
		return false;

	for (i=0; i<normal_len && chosen_card==false; i++) // iter all the types and then all the player's cards
	{
		for (j=0; j<pPlayers[pStatus->player_turn].card_count && chosen_card==false; j++)
		{
			if (normal_list[i]==pPlayers[pStatus->player_turn].cards[j].type)
			{
				chosen_card = true;
				if (selected_card!=NULL)
					*selected_card = j;
			}
		}
	}

	if (chosen_card==false) // if nothing has been found... then chose a djanni mode if available
	{
		if (core_game_ai_can_djanni_triple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==true)
		{
			pEnv->selected_djanni_mode = DM_TRIPLE;
			return true;
		}
		else if (core_game_ai_can_djanni_couple(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv, selected_card)==true)
		{
			pEnv->selected_djanni_mode = DM_COUPLE;
			return true;
		}
	}

	return chosen_card;
}

_Bool core_game_ai_pickup_best_card(const Player * pPlayer, int * selected_card)
{
	static const CardType wish_list[] = {
		MEOOOW, //1
		ATTACK, //5
		SKIP, //6
		NOPE, //3
		FAVOR, //7
		SHUFFLE, //2
		SEE_THE_FUTURE, //4
		DJANNI_CARDS, //8
		EXPLODING_DJANNI, //0 (even if impossible)
	};
	static const int wish_len = sizeof(wish_list)/sizeof(CardType);
	_Bool chosen_card = false;
	int i, j;
	if (pPlayer==NULL || pPlayer->card_count<=0) // skip null ptr or cards<=0
		return false;

	if (pPlayer->card_count<=0) // skip if empty
		return false;

	for (i=0; i<wish_len && chosen_card==false; i++) // iter all the types and then all the player's cards
	{
		for (j=0; j<pPlayer->card_count && chosen_card==false; j++)
		{
			if (wish_list[i]==pPlayer->cards[j].type)
			{
				chosen_card = true;
				if (selected_card!=NULL)
					*selected_card = j;
			}
		}
	}
	return chosen_card;
}

_Bool core_game_ai_pickup_worst_card(const Player * pPlayer, int * selected_card)
{
	static const CardType trash_list[] = {
		MEOOOW, //1
		ATTACK, //5
		SKIP, //6
		NOPE, //3
		FAVOR, //7
		SHUFFLE, //2
		SEE_THE_FUTURE, //4
		DJANNI_CARDS, //8
		EXPLODING_DJANNI, //0 (even if impossible)
	}; // read vice versa than the wish_list
	static const int trash_len = sizeof(trash_list)/sizeof(CardType);
	_Bool chosen_card = false;
	int i, j;
	if (pPlayer==NULL || pPlayer->card_count<=0) // skip null ptr or cards<=0
		return false;

	if (pPlayer->card_count<=0) // skip if empty
		return false;

	for (i=trash_len-1; i>=0 && chosen_card==false; i--) // iter all the types and then all the player's cards
	{
		for (j=0; j<pPlayer->card_count && chosen_card==false; j++)
		{
			if (trash_list[i]==pPlayer->cards[j].type)
			{
				chosen_card = true;
				if (selected_card!=NULL)
					*selected_card = j;
			}
		}
	}
	return chosen_card;
}

_Bool core_game_ai_is_it_valuable_card_to_nope(const Player pPlayers[], int players_count, int player_index, const Card * used_card, const GameEnv * pEnv)
{
	static const CardType wish_list[CARD_TYPE_NUM] = {
		ATTACK, //5
		FAVOR, //7
		SKIP //6
	};
	int i;

	if (pPlayers==NULL || used_card==NULL || pEnv==NULL) // skip null ptr or cards<=0
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	if (pEnv->is_noped==true) // don't nope again if already noped
		return false;

	for (i=0; i<CARD_TYPE_NUM; i++)
	{
		if (wish_list[i]==used_card->type)
			return true;
	}

	if (used_card->type==DJANNI_CARDS && pEnv->selected_djanni_mode==DM_TRIPLE) // hardcoded djanni check
		return true;

	return false;
}

_Bool core_game_am_i_next(const Player pPlayers[], int players_count, int player_index, const GameStatus * pStatus, const GameEnv * pEnv, _Bool consider_is_attacked)
{
	int next_turn;
	if (pPlayers==NULL || pStatus==NULL) // skip null ptr
		return false;

	if (core_game_check_winners(pPlayers, players_count)==true) // we at least know that two are still alive
		return false;

	next_turn = pStatus->player_turn;
	if ((consider_is_attacked==true && pEnv->is_noped==false) || pStatus->is_attacked==false) // switch player's turn if not being attacked or has attacked others
	{
		// pick up a valid next turn
		do
		{
			next_turn = (next_turn + 1) % players_count; // rotate the turns if exceeds the max count
		}
		while (pPlayers[next_turn].is_alive==false); // repeat if the next is dead
	}

	return next_turn==player_index;
}

_Bool core_game_ai_can_djanni_couple(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv, int * selected_card)
{
	int i, j;
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	// check out-of-range issue
	if (player_index >= players_count)
		return false;

	for (i=0; i<pPlayers[player_index].card_count; i++) // iter until there's a match
	{
		for (j=0; j<pPlayers[player_index].card_count; j++)
		{
			if (i==j) // skip itself
				continue;
			if (pPlayers[player_index].cards[i].type==DJANNI_CARDS
				&& pPlayers[player_index].cards[j].type==DJANNI_CARDS
				&& (strcmp(pPlayers[player_index].cards[i].title, pPlayers[player_index].cards[j].title)==0)
			)
			{
				if (selected_card!=NULL)
					*selected_card = i;
				return true;
			}
		}
	}

	return false;
}

_Bool core_game_ai_can_djanni_triple(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv, int * selected_card)
{
	int i, j;
	int match_count = 0;
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	// check out-of-range issue
	if (player_index >= players_count)
		return false;

	for (i=0; i<pPlayers[player_index].card_count && match_count<DJANNI_TRIPLE_MATCH_NUM; i++) // iter until there are 2 matches
	{
		match_count = 0;
		for (j=0; j<pPlayers[player_index].card_count && match_count<DJANNI_TRIPLE_MATCH_NUM; j++)
		{
			if (i==j) // skip itself
				continue;
			if (pPlayers[player_index].cards[i].type==DJANNI_CARDS
				&& pPlayers[player_index].cards[j].type==DJANNI_CARDS
				&& (strcmp(pPlayers[player_index].cards[i].title, pPlayers[player_index].cards[j].title)==0)
			)
			{
				if (selected_card!=NULL)
					*selected_card = i;
				match_count++;
			}
		}
	}

	return match_count>=DJANNI_TRIPLE_MATCH_NUM;
}

