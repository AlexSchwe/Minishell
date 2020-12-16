/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandreschwerer <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:32:49 by alexandre         #+#    #+#             */
/*   Updated: 2020/10/23 15:04:51 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(void)
{
	char	buff[1024];

	getcwd(buff, 1024);
	write(1, buff, ft_strlen(buff));
	write(1, "\n", 1);
	return (0);
}

void	ft_exit(t_parse *commands)
{
	int num;
	int i;

	i = -1;
	ft_free_env(g_env_head);
	if (commands->next && commands->next->content)
	{
		if (commands->next->content[i + 1] == '-')
			i++;
		while (commands->next->content[++i])
		{
			if (!ft_isdigit(commands->next->content[i]))
			{
				ft_error("exit: numeric argument required",
				commands->content, 2);
				free_parser(commands);
				exit(255);
			}
		}
		num = (unsigned char)ft_atoi(commands->next->content);
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
		g_status = ft_cd(head->next) << 8;
	else if (!ft_strcmp("export", head->content))
		g_status = ft_export(head->next) << 8;
	else if (!ft_strcmp("unset", head->content))
		g_status = ft_unset(head->next) << 8;
	else if (!ft_strcmp("echo", head->content))
		g_status = ft_echo(head->next) << 8;
	else if (!ft_strcmp("exit", head->content))
		ft_exit(head);
	else if (!ft_strcmp("env", head->content))
		g_status = ft_print_env() << 8;
	else if (!ft_strcmp("pwd", head->content))
		g_status = ft_pwd() << 8;
	else
		return (1);
	return (0);
}
