/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschwere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:19:46 by aschwere          #+#    #+#             */
/*   Updated: 2019/10/12 20:01:51 by aschwere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1);
	if (!(dest = malloc((j + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	if (s1)
		while (s1[i])
		{
			dest[i] = s1[i];
			i++;
		}
	j = i;
	if (s2)
		while (s2[i - j])
		{
			dest[i] = s2[i - j];
			i++;
		}
	dest[i] = '\0';
	return (dest);
}
