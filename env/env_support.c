/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandreschwerer <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:32:49 by alexandre         #+#    #+#             */
/*   Updated: 2020/10/23 15:04:51 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_key(char *str)
{
	t_env *env;

	env = g_env_head->next;
	while (env)
	{
		if (!ft_strcmp(env->key, str))
			return (env->value);
		env = env->next;
	}
	if (!ft_strcmp(str, "?"))
		return (ft_itoa(g_status >> 8));
	return (NULL);
}

t_env	*create_env(char *key, char *value)
{
	t_env *dest;

	if (!(dest = malloc(sizeof(struct s_env))))
		return (NULL);
	dest->key = ft_strdup(key);
	dest->value = ft_strdup(value);
	dest->next = NULL;
	dest->previous = NULL;
	return (dest);
}

int		ft_print_env(void)
{
	t_env *env;

	env = g_env_head->next;
	while (env)
	{
		if (env->key)
		{
			write(1, env->key, ft_strlen(env->key));
			write(1, "=", 1);
			if (env->value)
				write(1, env->value, ft_strlen(env->value));
		}
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}

int		insert_env(t_env *first, t_env *new)
{
	if (!first || !new)
		return (1);
	if (first->next)
		first->next->previous = new;
	first->next = new;
	new->previous = first;
	return (0);
}

int		delete_env(t_env *env)
{
	if (env->next)
		env->next->previous = env->previous;
	if (env->previous)
		env->previous->next = env->next;
	free(env->key);
	free(env->value);
	free(env);
	return (0);
}
