#ifndef __EDJ_CORE_H__
#define __EDJ_CORE_H__

/* macro list */
#define CARD_TITLE_LEN 127 // +1; old: 31+1; length of the card titles
#define PLAYER_NAME 23 // +1; length of the players' name
#define PLAYER_COUNT 4 // total available players (it can be safely changed)
#define DIFFICULTY_MODE_NUM 3 // count of DifficultyMode
#define CARD_TYPE_NUM 9 // count of CardType
#define PLAYER_TYPE_NUM 2 // count of PlayerType
#define CARD_COUNT_NUM 3 // count of CardCountType
#define DJANNI_MODE_NUM 3 // count of DjanniModeType
#define STARTING_OTHER_CARDS_NUM 4 // number of other cards to give to each player on first turn
#define STARTING_MEOOOW_NUM 1 // number of meooow cards to give to each player on first turn
#define SEE_THE_FUTURE_FORESEE_NUM 3 // number of cards you can foresee with the see the future card
#define DJANNI_DOUBLE_MATCH_NUM 1 // +1;
#define DJANNI_TRIPLE_MATCH_NUM 2 // +1;
#define SAVEFILE_FILENAME "partita.sav" // default savefile filename (used if you input a blank string)
#define FILEPATH_LEN 259 // +1; the same of MAX_PATH on windows
#define AI_WORRIED_PCT 10 // pct of drawing an exploding djanni that would cause the ai to be worried
#define AI_PANIC_PCT 100 // pct of drawing an exploding djanni that would cause the ai to be in panic
#define AI_LAZY_PCT 15 // pct of doing nothing in that specific turn
#define AI_LAZY_BUT_CRAZY_PCT 10 // pct of using a safelife card in that specific turn when lazy
#define AI_WORRIED_BUT_LAZY_PCT 30 // pct of doing nothing in that specific turn when worried
#define AI_MORE_WORRIED_PCT 40 // pct of using a safelife card in that specific turn when worried
#define PCT_MIN 0
#define PCT_MAX 100

/* include list */
#include "common.h"
#include "log.h"
#include "core_structs.h"
#include "core_lists.h"
#include "core_init.h"
#include "core_ai.h"
#include "core_game.h"

/* prototype list */
extern void core_run(void);
extern void core_shutdown(Player pPlayers[], int players_count, CardDeck * pDeck);

extern void core_shuffle_deck(CardDeck * pGivenDeck);
extern void core_shuffle_deck_head(CardDeck * pGivenDeck);

extern void core_insert_deck_in_n(CardDeck * pGivenDeck, Card card, int n);
extern void core_remove_deck_n_card(CardDeck * pGivenDeck, int selected_card);
extern void core_remove_deck_head(CardDeck * pGivenDeck);
extern void core_remove_player_n_card(Player * pGivenPlayer, int selected_card);
extern void core_remove_player_card_type(Player * pGivenPlayer, CardType card_type);
extern void core_remove_player_first_matched_card(Player * pGivenPlayer, Card copy_card);
extern _Bool core_player_has_in(Player * pGivenPlayer, CardType card_type);

extern void core_player_give_card_n_to_player(Player * pGiver, Player * pReceiver, int selected_card);
extern void core_player_draw_from_deck(Player * pPlayer, CardDeck * pGivenDeck);
extern void core_player_draw_from_deck(Player * pPlayer, CardDeck * pGivenDeck);

extern int core_deck_count_of_type_n(const CardDeck * pGivenDeck, CardType card_type);
extern double core_deck_get_pct_of_type_n(const CardDeck * pGivenDeck, CardType card_type);
extern int core_player_count_of_type_n(const Player * pGivenPlayer, CardType card_type);
extern double core_player_get_pct_of_type_n(const Player * pGivenPlayer, CardType card_type);

extern const char * get_card_type_name(CardType card_type);
extern const char * get_player_type_name(PlayerType player_type);
extern const char * get_card_count_type_name(CardCountType card_count_type);
extern const char * get_difficulty_mode_name(DifficultyMode difficulty_mode);
extern const char * get_djanni_mode_name(DjanniMode djanni_mode);

extern void players_log_data(const Player * pPlayers, int players_count);
extern void player_log_turn_data(const Player * pPlayer, const GameStatus * pStatus);
extern void status_log_data(const GameStatus * pStatus);

extern void player_print_hand(const Player * pPlayer);
extern void player_print_secret_hand(const Player * pPlayer);
extern void player_print_n_card(const Player * pPlayer, int selected_card);
extern void player_log_print_n_card(const Player * pPlayer, int selected_card);

extern void deck_print_count(const CardDeck * pDeck);
extern void deck_log_print_count(const CardDeck * pDeck);

extern void deck_print_cards(const CardDeck * pDeck);
extern void deck_log_print_cards(const CardDeck * pDeck);

extern void deck_print_first_n_cards(const CardDeck * pDeck, int n);
extern void deck_log_print_first_n_cards(const CardDeck * pDeck, int n);

extern void player_print_all_card_counts(const Player pPlayers[], int players_count);
extern void player_log_print_all_card_counts(const Player pPlayers[], int players_count);

#endif

