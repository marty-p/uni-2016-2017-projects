#include "core_ai.h"

_Bool core_game_process_ai_player(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL) // skip null ptr
		return false;

	// check out-of-range issue
	if (pStatus->player_turn >= players_count)
		return false;

	return true;
}

_Bool core_game_ai_choose_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card)
{
	if (pPlayers==NULL || pDeck==NULL || pStatus==NULL || pEnv==NULL || selected_card==NULL) // skip null ptr
		return false;

	if (player_index>=players_count) // skip out-of-range
		return false;

	core_game_ai_pickup_best_card(&pPlayers[player_index], selected_card);

	// printf("You chose the following card:\n");
	// player_print_n_card(&pPlayers[player_index], *selected_card);

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

