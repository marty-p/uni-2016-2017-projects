#ifndef __EDJ_CORE_INIT_H__
#define __EDJ_CORE_INIT_H__

/* include list */
#include "core.h"

/* prototype list */
extern _Bool core_init(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus);
extern _Bool core_init_new_game(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus);
extern DifficultyMode core_init_choose_mode();
extern _Bool core_init_default_status(GameStatus * pStatus, Player pPlayers[], int players_count);
extern void core_init_default_players(Player pPlayers[], int players_count);

extern _Bool core_load_default_deck(Player pPlayers[], int players_count, CardDeck * pDeck, DifficultyMode mode_choice);
extern void core_assign_default_deck(Player pPlayers[], int players_count, CardDeck * pGivenDeck, int given_cards);

#endif

