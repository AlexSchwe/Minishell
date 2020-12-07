#include "minishell.h"

t_parse *ft_tail_parse(t_parse *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

void 	insert_list(t_parse *parse, t_parse *head)
{
	t_parse *next;
	t_parse *last;

	if (!head || !head->next || !parse)
		return;
	next = parse->next;
	head = head->next;
	parse->next = head;
	head->previous = parse;
	last = ft_tail_parse(head);
	last->next = next;
	last->space = parse->space;
	parse->space = 1; 
	if (next)
		next->previous = last;
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