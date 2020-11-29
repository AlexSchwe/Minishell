#include "minishell.h"

t_parse *ft_tail_parse(t_parse *head)
{
	while (head)
		head = head->next;
	return (head);
}

void 	insert_list(t_parse *parse, t_parse *head)
{
	t_parse *next;
	t_parse *last;

	if (!head || (parse))
		return;
	next = parse->next;
	parse->next = head;
	head->previous = parse;
	last = ft_tail_parse(head);
	last->next = next;
	if (next)
		next->previous = next;
}

void 	cut_parser(t_parse *current)
{
	if (!current)
		return;
	if (current->previous)
		current->previous->next = NULL;
	if (current->next)
		current->next->previous = NULL;
	if (current->content)
		free(current->content);
	free(current);
}