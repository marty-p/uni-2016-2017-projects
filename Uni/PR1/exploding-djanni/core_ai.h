#ifndef __EDJ_CORE_AI_H__
#define __EDJ_CORE_AI_H__

/* include list */
#include "core.h"

/* prototype list */
extern _Bool core_game_process_ai_player(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);
extern _Bool core_game_ai_continue(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);
extern _Bool core_game_ai_choose_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card);
extern _Bool core_game_ai_pickup_best_card(const Player * pPlayer, int * selected_card);

#endif

