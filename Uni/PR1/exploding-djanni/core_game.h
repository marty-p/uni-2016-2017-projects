#ifndef __EDJ_CORE_GAME_H__
#define __EDJ_CORE_GAME_H__

/* include list */
#include "core.h"

/* prototype list */
extern _Bool core_game_start(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus);
extern _Bool core_game_pause_menu(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus);

#endif

