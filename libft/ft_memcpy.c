/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschwere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 08:19:04 by aschwere          #+#    #+#             */
/*   Updated: 2019/10/16 08:26:23 by aschwere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char *tmpd;
	char *tmps;

	tmpd = (char*)dest;
	tmps = (char*)src;
	if (!(dest) && !(src))
		return (dest);
	while (n-- > 0)
	{
		*tmpd++ = *tmps++;
	}
	return (dest);
}
