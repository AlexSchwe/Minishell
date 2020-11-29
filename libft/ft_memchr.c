/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschwere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:33:44 by aschwere          #+#    #+#             */
/*   Updated: 2019/10/16 08:25:38 by aschwere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	char *tmp;

	tmp = (char*)src;
	c = (unsigned char)c;
	while (n-- > 0)
	{
		if ((unsigned char)*tmp == c)
			return (tmp);
		tmp++;
	}
	return (NULL);
}
