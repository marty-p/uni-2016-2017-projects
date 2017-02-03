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

_Bool core_game_ai_is_in_panic(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	return pEnv->saw_terrible_future;
}

_Bool core_game_ai_is_worried(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv)
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

	expdjanni_pct = core_deck_get_pct_of_type_n(pDeck, EXPLODING_DJANNI); // returns pct of drawing the exploding djanni card
	has_meooow = core_player_count_of_type_n(&pPlayers[pStatus->player_turn], MEOOOW) >= 1; // true if the player has at least 1 meooow

	if (has_meooow==false) // very simple check to be in panic
		return expdjanni_pct >= AI_WORRIED_PCT; // 25%

	return false;
}

_Bool core_game_ai_getting_lazy(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv)
{
	double lazy_pct;

	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
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
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	// set a death flag (it will set to false after some operations)
	pEnv->saw_terrible_future = core_game_ai_next_draw_means_death(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv);

	do // repeat until draw
	{
		log_write("elaborating ai continue...");
		player_log_turn_data(&pPlayers[pStatus->player_turn], pStatus);

		if (core_game_ai_getting_lazy(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv)==true) // if lazy (or empty-handed), draw a card
		{
			if (core_game_ai_draw_card(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
				return false;
		}
		else if (core_game_ai_is_in_panic(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv)==true) // try to escape death in any way possible
		{
			if (core_game_ai_use_first_save_life_card(pPlayers, players_count, pDeck, pStatus, pEnv)==false)
				return false;
		}
		else if (core_game_ai_is_worried(pPlayers, players_count, pStatus->player_turn, pDeck, pStatus, pEnv)==true) // try to play some cards to feel safe
		{
		}
		else // normal play
		{
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

	if (core_game_card_draw(pPlayers, players_count, pDeck, pStatus, pEnv)==false) // draw a card
		return false;

	pEnv->has_drawn = true; // the turn will end after this
	return true;
}

_Bool core_game_ai_use_first_save_life_card(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	if (pPlayers[pStatus->player_turn].card_count<=0)
		return true;

	return true;
}

_Bool core_game_ai_choose_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL || selected_card==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	core_game_ai_pickup_best_card(&pPlayers[player_index], selected_card);

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

_Bool core_game_ai_is_it_valuable_card_to_nope(const Player pPlayers[], int players_count, int player_index, const CardNode * used_card, const GameEnv * pEnv)
{
	static const CardType wish_list[CARD_TYPE_NUM] = {
		ATTACK, //5
		FAVOR, //7
		SKIP //6
	};
	int i;

	if (pPlayers==NULL || used_card==NULL || pEnv==NULL) // skip null ptr or cards<=0
		return false;

	for (i=0; i<CARD_TYPE_NUM; i++)
	{
		if (wish_list[i]==used_card->card.type)
			return true;
	}
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

