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

t_parse *dup_parse(t_parse *parse)
{
	t_parse *dest;

	if (!(dest = create_parse(NULL, parse->content, parse->alias, parse->prev, parse->space)))
		return(NULL);
	dest->type = parse->type;
	return (dest);
}

t_parse *dup_list(t_parse *head)
{
	t_parse *dest;
	t_parse *next;

	if (!head)
		return (NULL);
	dest = dup_parse(head);
	head = head->next;
	next = dest;
	while (head)
	{
		next->next = dup_parse(head);
		next->next->previous = next;
		head = head->next;
		next = next->next;
	}
	return (dest);
}