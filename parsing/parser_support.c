#include "minishell.h"

int len_parse(t_parse *parse)
{
	t_parse *current;
	int dest;

	current = parse;
	dest = 0;
	while (parse)
	{
		if (parse->content)
			dest++;
		parse = parse->next;
	}
	return (dest);
}

t_parse	*delete_parser(t_parse *current)
{
	t_parse *next;

	if (!current)
		return NULL;
	next = current->next;
	if (current->previous)
		current->previous->next = current->next;
	if (current->next)
		current->next->previous = current->previous;
	if (current->content)
		free(current->content);
	free(current);
	return (next);
}

int	free_parser(t_parse *head)
{
	t_parse *parser;
	t_parse *previous;

	parser = head;
	while (parser)
	{
		if (parser->content)
			free(parser->content);
		previous = parser;
		parser = parser->next;
		free(previous);
	}
return (0);
}

int merge_parse(t_parse *first, t_parse *second)
{
	char *content;

	if (!first || ! second)
		return (0);
	if (!first->content)
		content = second->content;
	else if (!second->content)
		content = first->content;
	else 
		content = ft_strjoin(first->content, second->content);
	free(first->content);
	first->content = content;
	first->next = second->next;
	first->space = second->space;
	delete_parser(second);
	return (0);
}

int merge_chevron(t_parse *head)
{
	t_parse *current;
	int i;

	current = head->next;
	i = 0;
	while (current && current->next)
	{
		if (!ft_strcmp(current->content, ">") && !ft_strcmp(current->next->content, ">"))
			if (!current->type && !current->next->type)
				if (!current->space)
					i = !(merge_parse(current, current->next));
		current = current->next;
	}
	return (i);
}