#include "minishell.h"

int					redir_node(t_cmd *cmd, pid_t *pid, int i)
{
	pipe(cmd->pipes);
	pid[i] = fork();
	if (pid[i] == -1)
		return (!ft_error(strerror(errno), "fork", 1));
	if (pid[i] == 0)
	{
		close_pipe_before(cmd);
		if (cmd->previous && dup2(cmd->previous->pipes[0], 0) < 0)
			return (!ft_error(strerror(errno), "|", 1));
		if (cmd->type == '|' && dup2(cmd->pipes[1], 1) < 0) //&& cmd_type == '|'
			return (!ft_error(strerror(errno), "|", 1));
		launch_cmd(cmd->head);
		if ((close(cmd->pipes[1]) < 0))
			return (!ft_error(strerror(errno), "|", 1));
		if (cmd->previous)
			if (close(cmd->previous->pipes[0]) < 0)
				return (!ft_error(strerror(errno), "|", 1));
		exit(g_status >> 8);
	}
	return (0);
}

t_cmd *launch_pipe(t_cmd *current, pid_t *pid)
{
	int i;

	i = -1;
	while (current->type == '|')
	{
		++i;
		redir_node(current, pid, i);
		current = current->next;
	}
	redir_node(current, pid, i);
	return (current);
}

/*
** Renvoie vers redir_node sur tous les t_cmd
** Ferme les pipes à la fin
*/

int					redir_cmds(t_cmd *head)
{
	t_cmd	*current;
	pid_t	*pid;
	int		i;

	if (!head)
		return (0);
	current = head;
	if (!current)
		return (1);
	pid = malloc((len_pipe(head) + 1) * sizeof(pid_t));
	current = launch_pipe(current, pid);
	i = -1;
	close_pipe(head);
	while (++i < len_pipe(head))
		waitpid(pid[i], &g_status, WUNTRACED);
	free(pid);
	return (0);
}