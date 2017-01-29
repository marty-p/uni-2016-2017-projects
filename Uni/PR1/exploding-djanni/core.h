#ifndef __EDJ_CORE_H__
#define __EDJ_CORE_H__

/* macro list */
#define CARD_TITLE_LEN 127 // +1; old: 31+1
#define PLAYER_NAME 23 // +1;
#define PLAYER_COUNT 4
#define DIFFICULTY_MODE_NUM 3
#define CARD_TYPE_NUM 9
#define PLAYER_TYPE_NUM 2
#define CARD_COUNT_NUM 3
#define STARTING_OTHER_CARDS_NUM 4
#define STARTING_MEOOOW_NUM 1
#define SAVEFILE_FILENAME "partita.sav"
#define FILEPATH_LEN 259 // +1; the same of MAX_PATH on windows

/* include list */
#include "common.h"
#include "log.h"
#include "core_structs.h"
#include "core_lists.h"
#include "core_init.h"

/* prototype list */
extern void core_run(void);
extern void core_shutdown(Player pPlayers[], int players_count, CardDeck * pDeck);

extern void core_shuffle_deck(CardDeck * pGivenDeck);

extern const char * get_card_type_name(CardType card_type);
extern const char * get_player_type_name(PlayerType player_type);
extern const char * get_card_count_type_name(CardCountType card_count_type);
extern const char * get_difficulty_mode_name(DifficultyMode difficulty_mode);

#endif

