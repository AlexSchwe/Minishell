/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandreschwerer <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:34:18 by alexandre         #+#    #+#             */
/*   Updated: 2020/10/21 15:38:02 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(t_parse *cmds)
{
	char	buff[1024];
	char	*path;

	if (cmds)
		path = cmds->content;
	else
		path = NULL;

	if (!(path))
		path = find_key("HOME");
	if (!(path))
		return (!ft_error("cd", "HOME not set", 1));
	if (chdir(path))
		return (!(ft_error("cd", strerror(errno), 1)));
	getcwd(buff, 1024);
	export_env("OLDPWD", find_key("PWD"));
	export_env("PWD", buff);
	return (0);
}