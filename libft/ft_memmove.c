/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschwere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:10:55 by aschwere          #+#    #+#             */
/*   Updated: 2019/10/16 09:00:08 by aschwere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*srcc;
	char	*destc;
	size_t	i;

	i = -1;
	srcc = (char *)src;
	destc = (char *)dest;
	if (srcc < destc)
		while ((int)(--n) >= 0)
			*(destc + n) = *(srcc + n);
	else
		while (++i < n)
			*(destc + i) = *(srcc + i);
	return (dest);
}
