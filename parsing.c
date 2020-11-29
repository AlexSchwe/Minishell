#include "minishell.h"

t_parse	*set_parse_zero(char *begin, int i, t_parse *current)
{
	char c;

	c = begin[i];
	if (ft_isspace(c))
		if (current->previous)
			current->previous->space = 1;
	if (c == '\'' || c == '\"')
		current->type = c;
	if (c == '$')
		current->alias = 1;
	current->prev = i + 1 - current->alias;
	return (current);
}

/*
***Remplis les structures t_parse
***Passe le type de guillemet dans parse->type
*/

t_parse *set_parse_redir(char *begin, int i, t_parse *current)
{
	char c;

	c = begin[i];
	if (i - current->prev > 0)
		current = set_parse(begin, i, current);
	current->prev = i;
	current = set_parse(begin, i + 1, current);
	current->prev -= 1;
	return (current);
}

t_parse *set_parse_alias(char *begin, int i, t_parse *current)
{
	int type;

	type = current->type;

	current = set_parse(begin, i, current);
	current->prev -= 1;
	current->type = type;
	return (current);
}

/*
***Remplis les structures t_parse
***Passe le type de guillemet dans parse->type
*/

t_parse *set_parse(char *begin, int i, t_parse *current)
{
	t_parse *next;
	char c;
	int alias;

	c = begin[i];
	alias = (c == '$') ? 1 : 0;
	if (((!current->type || (c != '\'' && c != '\"'))) && i - current->prev < 1)
		return (set_parse_zero(begin, i, current));
	if (!current->space)
		current->space = (c && ft_strrchr("\t \n\v\f\r", c)) ? 1 : 0;
	current->content = ft_strndup(begin + current->prev, i - current->prev);
	next = create_parse(current, NULL, alias, i + 1 - alias, 0);
	next->type = 0;
	if (next->alias || c == '$')
		next->type = current->type;
	if ((c == '\'' || c == '\"') && current->type != c)
		next->type = c;
	current->next = next;
	return (next);
}

t_parse *cmd_to_parser(char *str)
{
	int i;
	t_parse *current;
	t_parse *head;

	if (!str)
		return (NULL);
	i = -1;
	head = set_head_parser();
	current = head;
	while (str[++i])
	{
		if (ft_strrchr("\'\"\t \n\v\f\r", str[i]) && 
		(!current->type || current->type == str[i]))
			current = set_parse(str, i, current);
		else if(ft_strrchr("><|;", str[i]) && !current->type)
			current = set_parse_redir(str, i, current);
		else if (str[i] == '$' && current->type != '\'')
			current = set_parse(str, i, current);
		else if (current->alias && !ft_isalnum(str[i]) &&  str[i] != '_')
			current = set_parse_alias(str, i, current);
		else if (str[i] == '\\' && current->type != '\'')
			i++;
	}
	set_tail(str, i, current);
	merge_chevron(head);
	return (head);
}