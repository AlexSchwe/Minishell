#include "minishell.h"

/*
*** détecte et renvoie vers les built-ins 
*** ou executables pertinents
*/

int	exec_cmd(t_parse *head)
{
	pid_t pid;

	if (!head || !head->content)
		return (0);
	if (!ft_check_built_in(head))
		return (0);
	g_status = 0;
	pid = fork();
	if (pid == -1)
		ft_error(strerror(errno), "", 1);
	if (pid == 0)
		parse_child(head);
	if (pid > 0)
		waitpid(pid, &g_status, WUNTRACED);
	return (0);
}

/*
*** save stdin and stdout
*** apply ft_replace, which replaces ">", "<" and "$"
*** and exec 
*/

int	launch_cmd(t_parse *head)
{
	int ret;
	int defout;
	int defin;

	if ((defout = dup(STDOUT_FILENO)) < 0 || (defin = dup(STDIN_FILENO)) < 0)
			ft_error(strerror(errno), "", 1);
	if (!ft_replace(head))
		ret = exec_cmd(head->next);
	else
		ret = 1;
	if ((dup2(defout, STDOUT_FILENO)) < 0 || (dup2(defin, STDIN_FILENO)) < 0)
		ft_error(strerror(errno), "", 1);
	return (ret);
}

/*
*** extrait les commandes (sous forme de t_parse) puis les répartit en listes
*** en fonction des pipes (sous forme de t_cmd)
*/

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

void	ft_prompt(void)
{
	write(1, "minishell$", 10);
}

int		main(int argc, char **argv, char **env)
{
	char *line;
	(void)argc;
	(void)argv;

	set_env(env);
	signal_set_up(&ft_handle_signal);
//	ft_prompt();

	while (get_next_line(0, &line))
	{
		signal_set_up(&ft_handle_signal_child);
		minishell(line);
		free(line);
//		ft_prompt();
		signal_set_up(&ft_handle_signal);
	}
	return (ft_eof());
}