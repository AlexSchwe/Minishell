#include "minishell.h"

int		file_transfer(int fds, int fdd)
{
	int		ret;
	char	buf[65];

	while ((ret = read(fds, buf, 64)) > 0)
	{
		buf[ret] = '\0';
		if (write(fdd, buf, ft_strlen(buf)) == -1)
			return (1);
	}
	return (0);
}

int 	merge_cmds(t_parse *head)
{
	t_parse *current;

	current = head->next;
	while (current)
	{
		if (!current->type && (!current->content || !ft_strlen(current->content)))
			current = delete_parser(current);
		else if (!current->space && current->next)
		{
			 if (merge_parse(current, current->next))
				return (1);
		}
		else
			current = current->next;
	}
	return (0);
}