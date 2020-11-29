/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschwere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:46:33 by aschwere          #+#    #+#             */
/*   Updated: 2019/10/15 15:18:04 by aschwere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nbwords(char const *s, char c)
{
	int i;
	int res;

	i = 0;
	res = 0;
	if (s == NULL)
		return (0);
	while ((s[i] == c) && (s[i]))
		i++;
	if (s[i])
		res += 1;
	while (s[i])
	{
		if ((s[i] == c) && (s[i + 1] != c) && (s[i + 1]))
			res += 1;
		i++;
	}
	return (res);
}

int		sizeword(char const *s, char c)
{
	int i;

	i = 0;
	while ((s[i]) && (s[i] != c))
		i++;
	return (i);
}

char	*nextword(char const *s, char *dest, char c)
{
	int		i;

	i = 0;
	while ((s[i] != c) && (s[i]))
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_free(char **dest)
{
	int i;

	i = 0;
	while (dest[i])
		free(dest[i]);
	free(dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!nbwords(s, c) || !(dest = malloc((nbwords(s, c) + 1)
													* sizeof(char*))))
		return (NULL);
	while (j < nbwords(s, c) && (s))
	{
		while ((s[i] == c) && (s[i]))
			i++;
		if (!(dest[j] = malloc((sizeword(&s[i], c) + 1) * sizeof(char))))
		{
			dest[j] = NULL;
			ft_free(dest);
			return (NULL);
		}
		dest[j] = nextword(&s[i], dest[j], c);
		i += sizeword(&s[i], c);
		j++;
	}
	dest[j] = NULL;
	return (dest);
}
