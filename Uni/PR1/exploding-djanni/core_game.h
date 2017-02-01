#ifndef __EDJ_CORE_GAME_H__
#define __EDJ_CORE_GAME_H__

/* include list */
#include "core.h"

/* prototype list */
extern _Bool core_game_start(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus);

extern _Bool core_game_check_winners(const Player pPlayers[], int players_count);
extern void core_game_print_winners(const Player pPlayers[], int players_count);
extern _Bool core_game_pause_menu(const Player pPlayers[], int players_count, const CardDeck * pDeck, const GameStatus * pStatus);
extern _Bool core_game_process(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);
extern _Bool core_game_get_next_turn(const Player pPlayers[], int players_count, GameStatus * pStatus, GameEnv * pEnv);

extern _Bool core_game_process_ai_player(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);
extern _Bool core_game_process_real_player(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);
extern _Bool core_game_continue_menu(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);

extern _Bool core_game_card_draw(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);
extern _Bool core_game_card_use(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);

extern _Bool core_game_card_can_nope(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int selected_card);
extern _Bool core_game_card_use_see_the_future(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);
extern _Bool core_game_card_use_favor(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);
extern _Bool core_game_card_use_djanni_cards(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv);

extern _Bool core_game_real_choose_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card);
extern _Bool core_game_ai_choose_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int * selected_card);

extern _Bool core_game_ai_pickup_best_card(const Player * pPlayer, int * selected_card);

extern _Bool core_game_process_player_card(Player pPlayers[], int players_count, int player_index, CardDeck * pDeck, GameStatus * pStatus, GameEnv * pEnv, int selected_card);

#endif

