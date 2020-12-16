/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:35:01 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/08 04:07:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_to_char(t_parse *parse)
{
	char	**dest;
	int		i;
	int		len;

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

t_parse	*create_parse(t_parse *current, char *content, int alias, int prev)
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
	next->space = 0;
	next->type = 0;
	next->previous = current;
	return (next);
}

void	print_parser(t_parse *head)
{
	t_parse *current;

	current = head->next;
	while (current)
	{
		if (current->content)
			write(1, current->content, ft_strlen(current->content));
		write(1, "\n", 1);
		current = current->next;
	}
}
