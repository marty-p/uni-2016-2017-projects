#ifndef __EDJ_CORE_LISTS_H__
#define __EDJ_CORE_LISTS_H__

#include "core.h"

/* prototype list */
extern void card_node_free(CardNode * first);
extern CardNode * card_node_insert_head(CardNode * first, Card card);
extern CardNode * card_node_insert_tail(CardNode * first, Card card);
extern int card_node_count(CardNode * first);
extern CardNode * card_node_remove_head(CardNode * first);
extern CardNode * card_node_remove(CardNode * first, int n);
extern CardNode * card_node_check_remove(CardNode * first, int n, _Bool * is_deleted);

extern void card_node_print(CardNode * first);
extern void card_node_log_print(CardNode * first);
extern void card_node_print_first_n(CardNode * first, int n);
extern void card_node_log_print_first_n(CardNode * first, int n);

extern CardNode * card_node_select_n(CardNode * first, int n, CardNode ** prev);
extern CardNode * card_node_find_first_n_type(CardNode * first, CardType n_type, CardNode ** prev);
extern CardNode * card_node_find_first_n_type_and_delete(CardNode * first, CardType n_type, _Bool * is_deleted);
extern CardNode * card_node_find_first_matched_card(CardNode * first, Card copy_card, CardNode ** prev);
extern CardNode * card_node_find_first_matched_card_and_delete(CardNode * first, Card copy_card, _Bool * is_deleted);
extern int card_node_count_of_type_n(const CardNode * first, CardType card_type);

#endif

