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
#include "core_init.h"

/* prototype list */
extern void core_run();
extern void core_shutdown(Player pPlayers[], int players_count, CardDeck * pDeck);
extern void core_shuffle_deck(CardDeck * pGivenDeck);

#endif

