/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_support_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:35:01 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/08 04:07:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	*ft_tail_parse(t_parse *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

void	insert_list(t_parse *parse, t_parse *head)
{
	t_parse *next;
	t_parse *last;

	if (!head || !parse)
		return ;
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

void	cut_parser(t_parse *current)
{
	if (!current)
		return ;
	if (current->previous)
		current->previous->next = NULL;
	current->previous = NULL;
	if (current->content)
		free(current->content);
	current->content = NULL;
}

t_parse	*dup_parse(t_parse *parse)
{
	t_parse *dest;

	if (!(dest = create_parse(NULL, ft_strdup(parse->content), parse->alias,
	parse->prev)))
		return (NULL);
	dest->type = parse->type;
	dest->space = parse->space;
	return (dest);
}

t_parse	*dup_list(t_parse *head)
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
