/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandreschwerer <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:36:02 by alexandre         #+#    #+#             */
/*   Updated: 2020/10/29 21:43:26 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_semi_pipe(char *content)
{
	return (!ft_strcmp(content, ";") || !ft_strcmp(content, "|"));
}

int		ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
	|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*ft_strndup(char *str, int size)
{
	int		len;
	char	*dest;
	int		i;

	if (!str || size < 0)
		return (NULL);
	len = (int)ft_strlen(str) > size ? size : (int)ft_strlen(str);
	if (!(dest = malloc(len + 1)))
		return (NULL);
	i = -1;
	while (str[++i] && i < len)
		dest[i] = str[i];
	dest[i] = '\0';
	return (dest);
}

int		ft_free_vec(char **vec)
{
	int i;

	if (!vec)
		return (1);
	i = -1;
	while (vec[++i])
	{
		free(vec[i]);
	}
	free(vec);
	return (0);
}

void	print_vec(char **vec)
{
	int	i;

	if (!vec)
		return ;
	i = -1;
	while (vec[++i])
	{
		write(1, vec[i], ft_strlen(vec[i]));
		write(1, "\n", 1);
	}
}
