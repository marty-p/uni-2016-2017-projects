#ifndef __EDJ_CORE_GAME_H__
#define __EDJ_CORE_GAME_H__

/* include list */
#include "core.h"

/* prototype list */
extern _Bool core_game_start(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus);
extern _Bool core_game_check_winners(const Player pPlayers[], int players_count);
extern _Bool core_game_pause_menu(const Player pPlayers[], int players_count, const CardDeck * pDeck, const GameStatus * pStatus);
extern _Bool core_game_process(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus);
extern _Bool core_game_get_next_turn(const Player pPlayers[], int players_count, GameStatus * pStatus, _Bool has_attacked);
extern _Bool core_game_process_ai_player(const Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, _Bool * has_attacked);
extern _Bool core_game_process_real_player(const Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus, _Bool * has_attacked);

#endif

