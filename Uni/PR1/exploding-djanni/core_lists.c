#include "core_lists.h"

void card_node_free(CardNode * first)
{
	CardNode * tmp = NULL;
	while (first != NULL)
	{
		tmp = first->next;
		free(first);
		first = tmp;
	}
}

CardNode * card_node_insert_head(CardNode * first, Card card)
{
	CardNode * new_first = malloc(sizeof(CardNode));
	if (new_first==NULL)
	{
		exit(EXIT_FAILURE);
		return NULL; // redundant line (not executed due to the exit call)
	}

	new_first->card = card;
	new_first->next = first;
	return new_first;
}

CardNode * card_node_insert_tail(CardNode * first, Card card)
{
	CardNode * tmp = first;
	if (first==NULL)
		return card_node_insert_head(first, card);

	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = card_node_insert_head(NULL, card);

	return first;
}

int card_node_count(CardNode * first)
{
	int count = 0;
	while (first != NULL)
	{
		count++;
		first = first->next;
	}
	return count;
}

CardNode * card_node_remove_head(CardNode * first)
{
	CardNode * tmp = first;
	if (first != NULL)
	{
		tmp = first->next;
		free(first);
	}
	return tmp;
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

	while (tmp != NULL && count <= n)
	{
		if (count==n)
		{
			prevtmp->next = tmp->next;
			free(tmp);
			return first;
		}
		else
		{
			prevtmp = tmp;
			tmp = tmp->next;
			count++;
		}
	}

	return first;
}

void card_node_print(CardNode * first)
{
	while (first!=NULL)
	{
		printf("\t[%d]%s: %s\n", first->card.type, get_card_type_name(first->card.type), first->card.title);
		first = first->next;
	}
}

void card_node_log_print(CardNode * first)
{
	while (first!=NULL)
	{
		log_write("\t[%d]%s: %s\n", first->card.type, get_card_type_name(first->card.type), first->card.title);
		first = first->next;
	}
}

