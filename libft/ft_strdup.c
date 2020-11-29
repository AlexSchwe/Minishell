/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschwere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:28:45 by aschwere          #+#    #+#             */
/*   Updated: 2019/10/16 08:41:11 by aschwere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		i;

	i = 0;
	if (src)
		while (src[i])
			i++;
	if (!(copy = malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	if (src)
		while (src[i])
		{
			copy[i] = src[i];
			i++;
		}
	copy[i] = '\0';
	return (copy);
}
