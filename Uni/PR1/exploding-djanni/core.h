#ifndef __EDJ_CORE_H__
#define __EDJ_CORE_H__

/* macro list */
#define CARD_TITLE_LEN 127 //31
#define PLAYER_NAME 23
#define PLAYER_COUNT 4
#define DECKS_PATH_LEN 260

/* include list */
#include "common.h"
#include "log.h"
#include "core_structs.h"
#include "core_lists.h"

/* prototype list */
extern void core_run();
extern _Bool core_init_new_game(Player pPlayers[], CardDeck * pDeck, GameStatus * pStatus);
extern void core_assign_default_status(GameStatus * pStatus);
extern void core_assign_default_players(Player pPlayers[]);
extern void core_assign_default_deck(Player pPlayers[], CardDeck * pDeck, int given_cards);
extern _Bool core_load_default_deck(Player pPlayers[], CardDeck * pDeck, DifficultyMode mode_choice);

#endif

