/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschwere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 08:47:02 by aschwere          #+#    #+#             */
/*   Updated: 2019/10/16 08:15:14 by aschwere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	unsigned char *tmpd;
	unsigned char *tmps;

	tmpd = (unsigned char*)d;
	tmps = (unsigned char*)s;
	c = (unsigned char)c;
	while (n-- > 0)
	{
		if (*tmps == c)
		{
			*tmpd++ = *tmps++;
			return (tmpd);
		}
		*tmpd++ = *tmps++;
	}
	return (NULL);
}
