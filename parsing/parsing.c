#include "minishell.h"

t_parse *set_head_parser()
{
	t_parse *head;

	head = create_parse(NULL, NULL, 0, 0, 0);
	head->type = 0;
	head->next = create_parse(head, NULL, 0, -1, 0);
	head->next->type = 0;
	return (head);
}

/*
***Découpe en plusieurs mots en fonction des guillemets
*/
void	set_tail(char *str, int i, t_parse *current)
{
	if (!current)
		return;
	if (i > current->prev + 1)
		current->content = ft_strndup(str + current->prev + 1, i - current->prev - 1);
	else
		delete_parser(current);
}

t_parse *set_parse_alias(char *str, int i, t_parse *current)
{
	t_parse *next;
	int status;

	next = current;
	status = (str[i] == '?') ? 1 : 0;
	next->space = ft_strrchr("\t \n\v\f\r", str[i]) ? 1 : 0;
	next->content = ft_strndup(str + next->prev + 1, i - next->prev - 1 + status);
	next = create_parse(next, NULL, 0, 0, 0);
	next->prev = i - 1 + status;
	next->alias = (str[i] == '$') ? 1 : 0;
	if (ft_strrchr("\'\"", str[i]) && current->type != str[i])
		next->type = str[i];
	next->type = next->alias ? current->type : next->type;
	return (next);
}

t_parse *set_parse(char *str, int i, t_parse *current)
{
	t_parse *next;

	next = current;
	if (ft_strrchr("\t \n\v\f\r", str[i]) && !current->type)
		next->space = 1;
	if (i > next->prev + 1 || next->type == str[i])
	{
		next->content = ft_strndup(str + next->prev + 1, i - next->prev - 1);
		next = create_parse(next, NULL, 0, 0, 0);
	}
	next->alias = (str[i] == '$') ? 1 : 0;
	next->prev = i - next->alias;
	if (ft_strrchr("\'\"", str[i]) && current->type != str[i])
		next->type = str[i];
	next->type = next->alias ? current->type : next->type;
	if (ft_strrchr("><|;", str[i]))
	{
		next->content = ft_strndup(&str[i], 1);
		next = create_parse(next, NULL, 0, i, 0);
	}
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
	current = head->next;
	while (str[++i])
	{
		if (ft_strrchr("\'\"\t \n\v\f\r", str[i]) && 
		(!current->type || current->type == str[i]))
			current = set_parse(str, i, current);
		else if(ft_strrchr("><|;", str[i]) && !current->type)
			current = set_parse(str, i, current);
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