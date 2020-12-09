#include "minishell.h"

/*
** Ferme tous les pipes précédents
*/

int	close_pipe_before(t_cmd *cmd)
{
	t_cmd *current;

	current = cmd;
	if (!current)
		return (-1);
	if ((close(current->pipes[0]) < 0))
		ft_error(strerror(errno), "|", 1);
	current = current->previous;
	if (!current)
		return (0);
	if ((close(current->pipes[1]) < 0))
		ft_error(strerror(errno), "|", 1);
	while (current->previous != NULL)
	{
		current = current->previous;
		if ((close(current->pipes[0]) < 0))
			ft_error(strerror(errno), "|", 1);
		if ((close(current->pipes[1]) < 0))
			ft_error(strerror(errno), "|", 1);
	}
	return (0);
}

/*
** Ferme tous les pipes
*/

int	close_pipe(t_cmd *head)
{
	t_cmd *current;

	current = head;
	while (current)
	{
		if ((close(current->pipes[0]) < 0))
			ft_error(strerror(errno), "|", 1);
		if ((close(current->pipes[1]) < 0))
			ft_error(strerror(errno), "|", 1);
		current = current->next;
	}
	return (0);
}

void print_list(t_cmd *head)
{
	t_cmd *node;

	node = head;
	while (node)
	{
		print_parser(node->head);
		write(1, "type =", 6);
		write(1, &node->type, 1);
		write(1, "\n", 1);
		node = node->next;
	}
}

t_cmd *create_cmd(t_parse *head, t_cmd *prev)
{
	t_cmd *dest;

	if (!(dest = malloc(sizeof(struct s_cmd))))
				return (NULL);
	dest->head = head;
	dest->type = 0;
	dest->previous = prev;
	dest->next = NULL;
	return (dest);
}

t_cmd *set_list(t_parse *head)
{
	t_parse *next;
	t_cmd *new_head;
	t_cmd *next_lst;
	
	next = head->next;
	new_head = create_cmd(head, NULL);
	next_lst = new_head;
	while (next)
	{
		if (next->next && next->content && !next->type &&
		is_semi_pipe(next->content))
		{
			next_lst->next = create_cmd(next, next_lst);
			next_lst->type = next->content[0];
			cut_parser(next);
			next_lst = next_lst->next;
		}
		next = next->next;
	}
	next_lst->next = NULL;
	return (new_head);
}
