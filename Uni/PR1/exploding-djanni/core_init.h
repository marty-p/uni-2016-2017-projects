#ifndef __EDJ_CORE_INIT_H__
#define __EDJ_CORE_INIT_H__

/* include list */
#include "core.h"

/* prototype list */
extern _Bool core_init(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus);
extern _Bool core_init_new_game(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus);
extern _Bool core_init_load_game(Player pPlayers[], int players_count, CardDeck * pDeck, GameStatus * pStatus);
extern _Bool core_init_save_game(const Player pPlayers[], int players_count, const CardDeck * pDeck, const GameStatus * pStatus);

extern DifficultyMode core_init_choose_mode(void);
extern _Bool core_init_default_status(GameStatus * pStatus, Player pPlayers[], int players_count);
extern void core_init_default_players(Player pPlayers[], int players_count);

extern _Bool core_load_default_deck(Player pPlayers[], int players_count, CardDeck * pDeck, DifficultyMode mode_choice);
extern void core_assign_default_deck(Player pPlayers[], int players_count, CardDeck * pGivenDeck, int given_cards);
extern void core_merge_default_deck(CardDeck * pMainDeck, CardDeck * pGivenDeck);

#endif

