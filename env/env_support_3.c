/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_support_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandreschwerer <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:32:49 by alexandre         #+#    #+#             */
/*   Updated: 2020/10/23 15:04:51 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(void)
{
	t_env *env;
	t_env *prev;

	env = g_env_head;
	while (env)
	{
		prev = env;
		env = env->next;
		delete_env(prev);
	}
}
