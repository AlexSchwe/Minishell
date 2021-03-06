/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandreschwerer <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:32:49 by alexandre         #+#    #+#             */
/*   Updated: 2020/10/23 15:04:51 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_error(t_env *env)
{
	int i;

	i = -1;
	if (!env)
		return (!ft_error("export: not a valid identifier", "\0", 1));
	if (!env->key || !ft_strlen(env->key))
	{
		delete_env(env);
		return (!ft_error("export: not a valid identifier", "\0", 1));
	}
	while (env->key[++i])
	{
		if (!ft_isalnum(env->key[i]) && env->key[i] != '_')
		{
			ft_error("export: not a valid identifier", env->key, 1);
			delete_env(env);
		}
	}
	return (0);
}

int	ft_export(t_parse *parse)
{
	t_env *env;
	t_env *prev;

	if (!parse || !parse->content ||
	(parse->content && !ft_strcmp(parse->content, "-p")))
		return (export_p());
	env = create_env_str(parse->content);
	if (ft_export_error(env))
		return (1);
	if ((prev = find_env(env->key)))
	{
		free(prev->value);
		prev->value = ft_strdup(env->value);
		delete_env(env);
	}
	else
		insert_last(env);
	return (0);
}
