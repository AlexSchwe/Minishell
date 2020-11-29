/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandreschwerer <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:32:49 by alexandre         #+#    #+#             */
/*   Updated: 2020/10/23 15:04:51 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_n(t_parse *parse)
{
	int j;
	int n;

	n = 0;
	if (parse && parse->content)
	{
		while (parse && !ft_strncmp(parse->content, "-n", 2))
		{
			j = 2;
			while (parse->content[j] && parse->content[j] == 'n')
				j++;
			if (!parse->content[j])
				n = 1;
			else
				return (n);
		free(parse->content);
		parse->content = NULL;
		merge_parse(parse, parse->next);
		}
	}
	return (n);
}

int  ft_echo(t_parse *parse)
{
	int n;
	int i;

	i = 0;
	n = ft_echo_n(parse);
	while (parse && parse->content)
	{
		write(1, parse->content, ft_strlen(parse->content));
		if (parse->next->content)
			write(1, " ", 1);
		parse = parse->next;
	}
	if (!(n))
		write(1, "\n", 1);
	return (0);
}