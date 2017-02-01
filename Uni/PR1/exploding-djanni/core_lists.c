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

void card_node_print(CardNode * first)
{
	while (first!=NULL) // skip null ptr
	{
		// print all its values
		printf("\t[%d]%s: %s\n", first->card.type, get_card_type_name(first->card.type), first->card.title);
		first = first->next;
	}
}

void card_node_log_print(CardNode * first)
{
	while (first!=NULL) // skip null ptr
	{
		// log all its values
		log_write("\t[%d]%s: %s", first->card.type, get_card_type_name(first->card.type), first->card.title);
		first = first->next;
	}
}

void card_node_print_first_n(CardNode * first, int n)
{
	int count = 0;
	while (first!=NULL && count++<n) // skip null ptr
	{
		// print all its values
		printf("\t(%d) [%d]%s: %s\n", count, first->card.type, get_card_type_name(first->card.type), first->card.title);
		first = first->next;
	}
}

void card_node_log_print_first_n(CardNode * first, int n)
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

int card_node_count_of_type_n(CardNode * first, CardType card_type) // node counter O(n)
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

