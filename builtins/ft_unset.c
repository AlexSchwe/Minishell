/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandreschwerer <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:32:49 by alexandre         #+#    #+#             */
/*   Updated: 2020/10/23 15:04:51 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_parse *cmds)
{
	int		i;
	t_env	*env;
	char	*command;

	if (!cmds)
		return (0);
	command = cmds->content;
	i = -1;
	if (!cmds->content || !ft_strlen(cmds->content))
		return (!ft_error("unset not a valid identifier", "", 1));
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
	return (0);
}
