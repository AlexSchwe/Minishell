#include "minishell.h"


int	launch_cmd(t_parse *head)
{
	pid_t pid;

	if (ft_replace(head))
		return (1);
	g_status = 0;
	if (!ft_check_built_in(head))
		return (0);
	pid = fork();
	if (pid == -1)
		ft_error(strerror(errno), "", 1);
	if (pid == 0)
		parse_child(head);
	if (pid > 0)
		waitpid(pid, &g_status, WUNTRACED);
	return (0);
}

int	minishell(char *line)
{
	t_parse *parser;
	t_cmd *head;
	t_cmd *cmd;

	parser = cmd_to_parser(line);
	if (ft_syntax_error(parser))
		return (!(free_parser(parser)));
	head = set_list(parser);
	cmd = head;
	while (cmd)
	{
		if (cmd->type == '|')
			redir_cmds(cmd);
		else
			launch_cmd(cmd->head);
		while (cmd && cmd->type == '|')
			cmd = cmd->next;
			cmd = cmd->next;
	}
	free_cmd(head);
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	char *line;
	(void)argc;
	(void)argv;

	set_env(env);
	while (get_next_line(0, &line))
	{
		minishell(line);
		free(line);
	}
	return (0);
}