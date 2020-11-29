/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschwere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:31:04 by aschwere          #+#    #+#             */
/*   Updated: 2019/11/15 09:53:36 by aschwere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

char	*readline(char *str, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t bytes_read;
	char	*tmp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0 && (!(isin('\n', buffer, bytes_read))))
	{
		buffer[bytes_read] = '\0';
		tmp = str;
		str = ft_strjoin(str, buffer);
		free(tmp);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	buffer[bytes_read] = '\0';
	tmp = str;
	str = ft_strjoin(str, buffer);
	free(tmp);
	return (str);
}

int		isin(char c, const char *s, int len)
{
	int i;

	i = 0;
	while (s[i] && i < len)
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_advance(char **str, int i)
{
	char *tmp;

	tmp = *str;
	*str = ft_substr(*str, i, ft_strlen(*str) - i);
	free(tmp);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[10];
	int			i;
	int			res;
	char		*buff[BUFFER_SIZE];

	if (fd < 0 || BUFFER_SIZE < 1 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!str[fd])
		str[fd] = ft_strdup("");
	str[fd] = readline(str[fd], fd);
	if (str[fd][(i = 0)])
	{
		while ((str[fd][i]) && (str[fd][i] != '\n'))
			i++;
		res = (str[fd][i] == '\n') ? 1 : 0;
		if (i == 0)
			*line = ft_strdup("");
		else
			(*line) = ft_substr(str[fd], 0, i);
		ft_advance(&str[fd], i + 1);
		return (res);
	}
	(*line) = ft_strdup("");
	return (0);
}
