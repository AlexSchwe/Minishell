#include "minishell.h"

int double_quote(t_parse *parse)
{
	int i;
	int j;
	char *dest;
	char *str;

	str = parse->content;
	if (!parse || !parse->content)
		return (1);
	i = -1;
	j = -1;
	if (!(dest = calloc(ft_strlen(parse->content) + 1, sizeof(char))))
		return (1);
	while (str[++i])
	{
		if (str[i] == '\\' && str[i + 1] && !ft_strchr("\\\"$~\n", str[i + 1]))
			i++;
		dest[++j] = str[i];
	}
	dest[++j] = '\0';
	free(parse->content);
	parse->content = dest;
	return (0);
}

int apply_parse(t_parse *parse)
{
	int i;
	int j;
	char *dest;
	char *str;

	str = parse->content;
	if (!parse || !parse->content)
		return (1);
	i = -1;
	j = -1;
	if (!(dest = calloc(ft_strlen(parse->content) + 1, sizeof(char))))
		return (1);
	while (str[++i])
	{
		if (str[i] == '\\' && str[i + 1])
			i++;
		dest[++j] = str[i];
	}
	dest[++j] = '\0';
	free(parse->content);
	parse->content = dest;
	return (0);
}

t_parse *alias_to_parser(char *str)
{
	int i;
	int prev;
	t_parse *current;
	t_parse *head;

	i = 0;
	while (str[i] && ft_strrchr("\t \n\v\f\r", str[i]))
		i++;
	head = set_head_parser();
	current = head;
	prev = i--;
	while (str[++i])
	{
		if (ft_strrchr("\t \n\v\f\r", str[i]))
		{
			if (i > prev)
			{
				current->content = ft_strndup(str + prev, i - prev);
				current = create_parse(current, NULL, 0, 0, 0);
			}
			current->space = 1;
			prev = i + 1;
		}
	}
	current->content = ft_strndup(str + prev, i - prev);
	return (head);
}

int 	apply_alias(t_parse *parse)
{
	char *value;
	t_parse *new;

	if (!parse || !parse->content)
		return (1);
	if (ft_strlen(parse->content) <= 1)
		return (0);
	value = find_key(parse->content + 1);
	value = value ? ft_strdup(value) : ft_strdup("");
	free(parse->content);
	if (parse->type == '\"')
	{
		parse->content = value;
		return (0);
	}
	new = alias_to_parser(value);
	free(value);
	if (!new)
		return (0);
	parse->content = new->content;
	if (new->next)
		insert_list(parse, new->next);
	free(new);
	return (0);
}

int ft_replace(t_parse *head)
{
	t_parse *parse;

	parse = head;
	if (ft_chevron(head))
		return (1);
	while (parse)
	{
		if (parse->alias)
		{
			if (apply_alias(parse))
				return (1);
		}
		else if (parse->type == '\"')
		{
			if (double_quote(parse))
				return (1);
		}
		else if (!parse->type)
			if (apply_parse(parse))
				return (1);
		parse = parse->next;
	}
	return (merge_cmds(head));
}