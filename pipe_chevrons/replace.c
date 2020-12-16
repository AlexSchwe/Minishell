/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:35:01 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/08 04:07:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		double_quote(t_parse *parse)
{
	int		i;
	int		j;
	char	*dest;
	char	*str;

	str = parse->content;
	if (!parse || !parse->content)
		return (1);
	i = -1;
	j = -1;
	if (!(dest = calloc(ft_strlen(parse->content) + 1, sizeof(char))))
		return (1);
	while (str[++i])
	{
		if (str[i] == '\\' && str[i + 1] && ft_strchr("\\\"$~\n", str[i + 1]))
			i++;
		dest[++j] = str[i];
	}
	dest[++j] = '\0';
	free(parse->content);
	parse->content = dest;
	return (0);
}

int		apply_parse(t_parse *parse)
{
	int		i;
	int		j;
	char	*dest;
	char	*str;

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

t_parse	*alias_to_parser(char *str)
{
	int		i;
	int		prev;
	t_parse	*current;
	t_parse	*head;

	i = 0;
	if (!str)
		return (NULL);
	head = set_head_parser();
	current = head->next;
	while (str[i] && ft_strrchr("\t \n\v\f\r", str[i]) && ++i)
		head->space = 1;
	prev = i--;
	while (str[++i])
	{
		if (ft_strrchr("\t \n\v\f\r", str[i]))
		{
			if ((i > prev) && (current->content = ft_strndup(str + prev, i - prev)))
				current = create_parse(current, NULL, 0, 0);
			current->space = 1;
			prev = i + 1;
		}
	}
	current->content = ft_strndup(str + prev, i - prev);
	return (head);
}

int		apply_alias(t_parse *parse)
{
	char	*value;
	t_parse *new;

	if (!parse || !parse->content)
		return (1);
	if (ft_strlen(parse->content) <= 1 && parse->space)
		return (0);
	value = find_key(parse->content + 1);
	value = value && ft_strcmp(parse->content, "$?") ? ft_strdup(value) : value;
	free(parse->content);
	if (parse->type == '\"' || !value)
		parse->content = value;
	if (parse->type == '\"' || !value)
		return (0);
	new = alias_to_parser(value);
	free(value);
	if (!new)
		return (0);
	if (!parse->previous->space)
		parse->previous->space = new->space;
	parse->content = ft_strdup(new->next->content);
	if (new->next->next)
		insert_list(parse, dup_list(new->next->next));
	free_parser(new);
	return (0);
}

int		ft_replace(t_parse *head)
{
	t_parse *parse;

	if (ft_chevron(head))
		return (1);
	parse = head->next;
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
