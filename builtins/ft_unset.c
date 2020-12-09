#include "minishell.h"

/*
**Refaire error zsh : no match found
*/

int	ft_unset(t_parse *cmds)
{
	int		i;
	t_env	*env;
	char *command;

	if (!cmds || !cmds->content)
		return (0);
	command = cmds->content;
	i = -1;
	while (command[++i])
		if (!(ft_isalnum(command[i])) && command[i] != '/' && command[i] != '_'
		&& command[i] != '-' && command[i] != '.')
			return (!ft_error("unset invalid parameter name", command, 1));
	i = -1;
	env = g_env_head->next;
	while (env)
	{
		if (env->key && !ft_strcmp(command, env->key))
			return (delete_env(env));
		env = env->next;
	}
	return (1);
}