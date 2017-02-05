#ifndef __EDJ_CORE_AI_H__
#define __EDJ_CORE_AI_H__

/* include list */
#include "core.h"

/* prototype list */
extern _Bool core_game_ai_is_in_panic(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv);
extern _Bool core_game_ai_is_worried(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv);
extern _Bool core_game_ai_getting_lazy(const Player pPlayers[], int players_count, int player_index, const CardDeck * pDeck, const GameStatus * pStatus, const GameEnv * pEnv);
extern _Bool core_game_process_ai_player(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);
extern _Bool core_game_ai_continue(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);
extern _Bool core_game_ai_draw_card(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);
extern _Bool core_game_ai_select_first_save_life_card(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card);
extern _Bool core_game_ai_select_first_trivial_card(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card);
extern _Bool core_game_ai_select_first_normal_card(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card);
extern _Bool core_game_ai_choose_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card);
extern _Bool core_game_ai_pickup_best_card(const Player * pPlayer, int * selected_card);
extern _Bool core_game_ai_is_it_valuable_card_to_nope(const Player pPlayers[], int players_count, int player_index, const Card * used_card, const GameEnv * pEnv);
extern _Bool core_game_am_i_next(const Player pPlayers[], int players_count, int player_index, const GameStatus * pStatus, const GameEnv * pEnv, _Bool consider_is_attacked);

#endif

