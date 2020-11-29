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

char **parse_to_char(t_parse *parse)
{
	char **dest;
	int i;
	int len;

	i = -1;
	len = len_parse(parse);
	if (!(dest = malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	while (++i < len && parse)
	{
		if (parse->content)
			dest[i] = parse->content;
		parse = parse->next;
	}
	dest[i] = NULL;
	return (dest);
}

t_parse *create_parse(t_parse *current, char *content, int alias, int prev, int space)
{
	t_parse *next;

	if (!(next = malloc(sizeof(struct s_parse))))
		return (NULL);
	if (current)
		current->next = next;
	next->next = NULL;
	next->content = content;
	next->alias = alias;
	next->prev = prev;
	next->space = space;
	next->previous = current;
	return(next);
}

void print_parser(t_parse *head)
{
	t_parse *current;

	current = head;

	while (current)
	{
		if (current->content)
			write(1, current->content, ft_strlen(current->content));
		write(1, "\n", 1);
		current = current->next;
	}
}

t_parse *set_head_parser()
{
	t_parse *head;


	if (!(head = malloc(sizeof(struct s_parse))))
		return (NULL);
	head->content = NULL;
	head->type = 0;
	head->next = NULL;
	head->space = 0;
	head->alias = 0;
	head->previous = NULL;
	head->prev = 0;
	return (head);
}

/*
***Découpe en plusieurs mots en fonction des guillemets
*/
void	set_tail(char *str, int i, t_parse *current)
{
	if (!current)
		return;
	if (i > current->prev)
		current->content = ft_strndup(str + current->prev, i - current->prev);
	else
		delete_parser(current);
}
