#include "minishell.h"

void	ft_pwd()
{
	char *pwd;

	pwd = find_key("PWD");
	if (!pwd)
		return;
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}


void	ft_exit(t_parse *commands)
{
	int num;
	int i;

	i = -1;
	ft_free_env(g_env_head);
	if (commands->next && commands->next->content)
	{
		while (commands->next->content[++i])
		{
			if (commands->next->content[i] < '0' || commands->next->content[i] > '9')
			{
				ft_error("exit: numeric argument required", commands->content, 2);
				free_parser(commands);
				exit(255);
			}
		}
		num = ft_atoi(commands->next->content);
	}
	else
		num = g_status >> 8;
	free_parser(commands);
	exit(num);
}

/*
***Renvoie vers le bon built in.
***Renvoie 0 si un builtin est détecté
***1 sinon
*/

int		ft_check_built_in(t_parse *head)
{
	if (!head->content)
		return (1);

	if (!ft_strcmp("cd", head->content))
		ft_cd(head->next);
	else if (!ft_strcmp("export", head->content))
		ft_export(head->next);
	else if (!ft_strcmp("unset", head->content))
		ft_unset(head->next);
	else if (!ft_strcmp("echo", head->content))
		ft_echo(head->next);
	else if (!ft_strcmp("exit", head->content))
		ft_exit(head);
	else if (!ft_strcmp("env", head->content))
		ft_print_env();
	else if (!ft_strcmp("pwd", head->content))
		ft_pwd();
	else
		return (1);
	return (0);
}