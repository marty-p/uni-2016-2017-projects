#include "core_lists.h"

void card_node_free(CardNode * first) // free all the nodes
{
	CardNode * tmp = NULL; // tmp var to store next
	while (first != NULL) // iter till null
	{
		// switch and free
		tmp = first->next;
		free(first);
		first = tmp;
	}
}

CardNode * card_node_insert_head(CardNode * first, Card card) // add the node in the head
{
	CardNode * new_first = malloc(sizeof(CardNode)); // allocate dynamic memory
	if (new_first==NULL) // exit if runtime errors happened
	{
		exit(EXIT_FAILURE);
		return NULL; // redundant line (not executed due to the exit call)
	}
	// assign the node values:
	new_first->card = card;
	new_first->next = first;
	return new_first; // it returns the updated head
}

CardNode * card_node_insert_tail(CardNode * first, Card card) // add the node in the end
{
	CardNode * tmp = first;
	if (first==NULL) // if first is null, then we add it in the head
		return card_node_insert_head(first, card);

	while (tmp->next != NULL) // itering till null
		tmp = tmp->next;
	tmp->next = card_node_insert_head(NULL, card); // adding the node in the end

	return first; // it returns the updated head
}

int card_node_count(CardNode * first) // node counter O(n)
{
	int count = 0; // counter
	while (first != NULL) // iter till null
	{
		count++; // incremented for each node
		first = first->next;
	}
	return count;
}

CardNode * card_node_remove_head(CardNode * first)
{
	CardNode * tmp = first;
	if (first != NULL) // skip null ptr
	{
		tmp = first->next; // switch to the next head
		free(first);
	}
	return tmp; // it returns the updated head
}

CardNode * card_node_remove(CardNode * first, int n)
{
	int count = 0;
	CardNode * tmp = first;
	CardNode * prevtmp = first;

	// check if the index is negative:
	if (n < 0)
		return first;

	// check if the index is the head:
	if (n==0)
		return card_node_remove_head(first);

	while (tmp != NULL && count <= n) // iter till null or n
	{
		if (count==n) // if n, it will be deleted
		{
			prevtmp->next = tmp->next;
			free(tmp);
			return first; // it returns the updated head
		}
		else // if not n, it counts and goes further
		{
			prevtmp = tmp;
			tmp = tmp->next;
			count++;
		}
	}

	return first; // it returns the updated head
}

CardNode * card_node_check_remove(CardNode * first, int n, _Bool * is_deleted)
{
	int count = 0;
	CardNode * tmp = first;
	CardNode * prevtmp = NULL;
	if (is_deleted!=NULL)
		*is_deleted = false;

	// check if the index is negative:
	if (n < 0)
		return first;

	// check if the index is the head:
	if (n==0)
	{
		if (is_deleted!=NULL)
			*is_deleted = true;
		return card_node_remove_head(first);
	}

	while (tmp != NULL && count <= n) // iter till null or n
	{
		if (count==n) // if n, it will be deleted
		{
			if (is_deleted!=NULL)
				*is_deleted = true;
			prevtmp->next = tmp->next;
			free(tmp);
			return first; // it returns the updated head
		}
		else // if not n, it counts and goes further
		{
			prevtmp = tmp;
			tmp = tmp->next;
			count++;
		}
	}

	return first; // it returns the updated head
}

void card_node_print(const CardNode * first)
{
	while (first!=NULL) // skip null ptr
	{
		// print all its values
		printf("\t[%d]%s: %s\n", first->card.type, get_card_type_name(first->card.type), first->card.title);
		first = first->next;
	}
}

void card_node_log_print(const CardNode * first)
{
	while (first!=NULL) // skip null ptr
	{
		// log all its values
		log_write("\t[%d]%s: %s", first->card.type, get_card_type_name(first->card.type), first->card.title);
		first = first->next;
	}
}

void card_node_print_first_n(const CardNode * first, int n)
{
	int count = 0;
	while (first!=NULL && count++<n) // skip null ptr
	{
		// print all its values
		printf("\t(%d) [%d]%s: %s\n", count, first->card.type, get_card_type_name(first->card.type), first->card.title);
		first = first->next;
	}
}

void card_node_log_print_first_n(const CardNode * first, int n)
{
	int count = 0;
	while (first!=NULL && count++<n) // skip null ptr
	{
		// log all its values
		log_write("\t[%d]%s: %s", first->card.type, get_card_type_name(first->card.type), first->card.title);
		first = first->next;
	}
}

CardNode * card_node_select_n(CardNode * first, int n, CardNode ** prev)
{
	int count=0;
	CardNode * tmp_prev = NULL;

	while (first!=NULL && count<=n) // skip null ptr
	{
		if (count==n)
		{
			if (prev!=NULL)
				*prev=tmp_prev;
			return first;
		}
		tmp_prev = first;
		first = first->next;
		count++;
	}
	return NULL;
}

CardNode * card_node_find_first_n_type(CardNode * first, CardType n_type, CardNode ** prev)
{
	CardNode * tmp_prev = NULL;

	while (first!=NULL) // skip null ptr
	{
		if (n_type==first->card.type)
		{
			if (prev!=NULL)
				*prev=tmp_prev;
			return first;
		}
		tmp_prev = first;
		first = first->next;
	}
	return NULL;
}

CardNode * card_node_find_first_n_type_and_delete(CardNode * first, CardType n_type, _Bool * is_deleted)
{
	CardNode * tmp_prev = NULL;
	CardNode * tmp = NULL;
	if (is_deleted!=NULL)
		*is_deleted = false;
	tmp = card_node_find_first_n_type(first, n_type, &tmp_prev);
	if (tmp!=NULL)
	{
		if (is_deleted!=NULL)
			*is_deleted = true;
		if (tmp_prev==NULL) // head
		{
			return card_node_remove_head(first);
		}
		tmp_prev->next = tmp->next;
		free(tmp);
		tmp=NULL;
	}
	return first;
}

CardNode * card_node_find_first_matched_card(CardNode * first, Card copy_card, CardNode ** prev)
{
	CardNode * tmp_prev = NULL;

	while (first!=NULL) // skip null ptr
	{
		if (copy_card.type==first->card.type && strcmp(copy_card.title, first->card.title)==0) // if type and title are the same
		{
			if (prev!=NULL)
				*prev=tmp_prev;
			return first;
		}
		tmp_prev = first;
		first = first->next;
	}
	return NULL;
}

CardNode * card_node_find_first_matched_card_and_delete(CardNode * first, Card copy_card, _Bool * is_deleted)
{
	CardNode * tmp_prev = NULL;
	CardNode * tmp = NULL;
	if (is_deleted!=NULL)
		*is_deleted = false;
	tmp = card_node_find_first_matched_card(first, copy_card, &tmp_prev);
	if (tmp!=NULL)
	{
		if (is_deleted!=NULL)
			*is_deleted = true;
		if (tmp_prev==NULL) // head
		{
			return card_node_remove_head(first);
		}
		tmp_prev->next = tmp->next;
		free(tmp);
		tmp=NULL;
	}
	return first;
}

int card_node_count_of_type_n(const CardNode * first, CardType card_type) // node counter O(n)
{
	int count = 0; // counter
	while (first != NULL) // iter till null
	{
		if (first->card.type==card_type)
			count++; // incremented for each node
		first = first->next;
	}
	return count;
}

void card_list_insert_head(Player * pPlayer, Card new_card)
{
	Card * new_cards = NULL;
	int i, j;
	if (pPlayer==NULL)
		return;

	new_cards = calloc(pPlayer->card_count+1, sizeof(Card));
	if (new_cards==NULL)
		exit(EXIT_FAILURE);

	new_cards[0] = new_card;
	for (i=1, j=0; j<pPlayer->card_count; i++, j++)
		new_cards[i] = pPlayer->cards[j];

	free(pPlayer->cards);
	pPlayer->cards = new_cards;
	pPlayer->card_count++;
}

void card_list_insert_tail(Player * pPlayer, Card new_card)
{
	Card * new_cards = NULL;
	int i, j;
	if (pPlayer==NULL)
		return;

	new_cards = calloc(pPlayer->card_count+1, sizeof(Card));
	if (new_cards==NULL)
		exit(EXIT_FAILURE);

	for (i=0, j=0; i<pPlayer->card_count; i++, j++)
		new_cards[i] = pPlayer->cards[j];
	new_cards[i] = new_card;

	free(pPlayer->cards);
	pPlayer->cards = new_cards;
	pPlayer->card_count++;
}

void card_list_remove_n(Player * pPlayer, int n)
{
	Card * new_cards = NULL;
	_Bool skip_first = false;
	int i, j;
	if (pPlayer==NULL)
		return;
	if (n<0 || n >= pPlayer->card_count)
		return;

	new_cards = calloc(pPlayer->card_count-1, sizeof(Card));
	if (new_cards==NULL)
		exit(EXIT_FAILURE);

	for (i=0, j=0; i<pPlayer->card_count; i++)
		if (i!=n)
			new_cards[j++] = pPlayer->cards[i];
		else
			skip_first = true;

	if (skip_first==true)
	{
		free(pPlayer->cards);
		pPlayer->cards = new_cards;
		pPlayer->card_count--;
	}
	else
		free(new_cards);
}

void card_list_remove_first_type_n(Player * pPlayer, CardType card_type)
{
	Card * new_cards = NULL;
	_Bool skip_first = false;
	int i, j;
	if (pPlayer==NULL)
		return;
	if (pPlayer->card_count <= 0)
		return;

	new_cards = calloc(pPlayer->card_count-1, sizeof(Card));
	if (new_cards==NULL)
		exit(EXIT_FAILURE);

	for (i=0, j=0; i<pPlayer->card_count; i++)
		if (skip_first==true || pPlayer->cards[i].type!=card_type)
			new_cards[j++] = pPlayer->cards[i];
		else
			skip_first = true;

	if (skip_first==true)
	{
		free(pPlayer->cards);
		pPlayer->cards = new_cards;
		pPlayer->card_count--;
	}
	else
		free(new_cards);
}

void card_list_remove_first_card_n(Player * pPlayer, Card copy_card)
{
	Card * new_cards = NULL;
	_Bool skip_first = false;
	int i, j;
	if (pPlayer==NULL)
		return;
	if (pPlayer->card_count <= 0)
		return;

	new_cards = calloc(pPlayer->card_count-1, sizeof(Card));
	if (new_cards==NULL)
		exit(EXIT_FAILURE);

	for (i=0, j=0; i<pPlayer->card_count; i++)
		if (skip_first==true || (copy_card.type==pPlayer->cards[i].type && strcmp(copy_card.title, pPlayer->cards[i].title)==0)==false)
			new_cards[j++] = pPlayer->cards[i];
		else
			skip_first = true;

	if (skip_first==true)
	{
		free(pPlayer->cards);
		pPlayer->cards = new_cards;
		pPlayer->card_count--;
	}
	else
		free(new_cards);
}

_Bool card_list_has_type_n(const Player * pPlayer, CardType card_type)
{
	_Bool has_it = false;
	int i;
	if (pPlayer==NULL)
		return false;

	for (i=0; i<pPlayer->card_count && has_it==false; i++)
		if (card_type==pPlayer->cards[i].type)
			has_it = true;
	return has_it;
}

int card_list_count_of_type_n(const Player * pPlayer, CardType card_type)
{
	int count = 0;
	int i;
	if (pPlayer==NULL)
		return false;

	for (i=0; i<pPlayer->card_count; i++)
		if (card_type==pPlayer->cards[i].type)
			count++;
	return count;
}

Card * card_list_select_n(Player * pPlayer, int n)
{
	if (pPlayer==NULL)
		return NULL;
	if (n<0 || n >= pPlayer->card_count)
		return NULL;

	return &pPlayer->cards[n];
}

const Card * card_list_const_select_n(const Player * pPlayer, int n)
{
	if (pPlayer==NULL)
		return NULL;
	if (n<0 || n >= pPlayer->card_count)
		return NULL;

	return &pPlayer->cards[n];
}

void card_list_log_print(const Player * pPlayer)
{
	int i;
	if (pPlayer==NULL)
		return;
	for (i=0; i<pPlayer->card_count; i++)
		log_write("\t[%d]%s: %s", pPlayer->cards[i].type, get_card_type_name(pPlayer->cards[i].type), pPlayer->cards[i].title);
}

