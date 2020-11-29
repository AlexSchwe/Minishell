/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschwere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:32:32 by aschwere          #+#    #+#             */
/*   Updated: 2019/10/13 12:57:14 by aschwere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		issep(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		isleft(char *s1, char const *set)
{
	int i;

	i = 0;
	while (s1[i])
	{
		if (!(issep(s1[i], set)))
			return (1);
		i++;
	}
	return (0);
}

int		ft_sizetrim(char const *s1, char const *set)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (issep(s1[i], set))
		i++;
	while (isleft((char*)&s1[size + i], set))
		size++;
	return (size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!(res = malloc((ft_sizetrim(s1, set) + 1) * sizeof(char))))
		return (NULL);
	while (issep(s1[i], set))
		i++;
	j = i;
	while (isleft((char*)&s1[i], set))
	{
		res[i - j] = s1[i];
		i++;
	}
	res[i - j] = '\0';
	return (res);
}
