/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschwere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:42:46 by aschwere          #+#    #+#             */
/*   Updated: 2019/10/13 11:58:58 by aschwere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		order(long int n)
{
	int res;

	res = 1;
	while (n > 9)
	{
		n = n / 10;
		res += 1;
	}
	return (res);
}

char	*ft_write(char *res, long int n, int size)
{
	int debut;

	if (res[0] == '-')
		debut = 1;
	else
		debut = 0;
	res[size] = '\0';
	size -= 1;
	while (size >= debut)
	{
		res[size] = n % 10 + '0';
		n = n / 10;
		size--;
	}
	return (res);
}

char	*ft_itoa(int nb)
{
	char		*res;
	int			size;
	int long	n;

	n = nb;
	if (n < 0)
	{
		n *= -1;
		if (!(res = malloc((order(n) + 2) * sizeof(char))))
			return (NULL);
		res[0] = '-';
		size = order(n) + 1;
	}
	else
	{
		size = order(n);
		if (!(res = malloc((order(n) + 1) * sizeof(char))))
			return (NULL);
	}
	res = ft_write(res, n, size);
	return (res);
}
