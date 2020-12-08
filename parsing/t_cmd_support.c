#include "minishell.h"

/*
*** Renvoie la taille de la suite de commande séparées par des pipes
*/

int len_pipe(t_cmd *head)
{
	int i;
	t_cmd *node;

	node = head;
	i = 0;
	while (node && node->type == '|')
	{
		i++;
		node = node->next;
	}
	return (i);
}

/*
*** Rend la liste bidirectionnelle
*/

void	set_previous(t_cmd *head)
{
	t_cmd *current;
	t_cmd *previous;

	if (!head)
		return;
	current = head->next;
	previous = head;
	previous->previous = NULL;
	while (current)
	{
		current->previous = previous;
		previous = current;
		current = current->next;
	}
}

/*
*** Libère la liste
*/

void free_cmd(t_cmd *head)
{
	t_cmd *current;
	t_cmd *previous;

	current = head;
	while (current)
	{
		free_parser(current->head);
		previous = current;
		current = current->next;
		free(previous);
	}
}