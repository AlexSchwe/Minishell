/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 10:35:01 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/08 04:07:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(char *file, char **commands, char *exec)
{
	char **env;

	env = array_env();
	if (execve(file, commands, env) == -1)
	{
		ft_error(strerror(errno), exec, 126);
		ft_free_vec(env);
		exit(126);
	}
}

/*
**recherche un exécutable dans tous les dossiers mentionnés par Path
*/

int		ft_parse_path(char *exec, char **commands, char **dir)
{
	char		*file;
	char		*tmp;
	struct stat	filestat;
	int			i;

	i = -1;
	while (dir[++i])
	{
		tmp = ft_strjoin(dir[i], "/");
		file = ft_strjoin(tmp, exec);
		free(tmp);
		if (lstat(file, &filestat) == 0 && (S_ISREG(filestat.st_mode)))
		{
			ft_free_vec(dir);
			ft_execve(file, commands, exec);
		}
		free(file);
	}
	ft_free_vec(dir);
	return (0);
}

/*
**recherche un exécutable dans tous les dossiers mentionnés par Path
**puis dans le dossier présent
*/

int		parse_child(t_parse *parse)
{
	char **path;
	char **commands;
	struct stat	filestat;

	commands = parse_to_char(parse);
	path = ft_split(find_key("PATH"), ':');
	if (path)
		ft_parse_path(parse->content, commands, path);
	if (lstat(parse->content, &filestat) == 0)
		ft_execve(parse->content, commands, parse->content);
	free(commands);
	ft_error("command not found", parse->content, 127);
	exit(g_status);
	return (1);
	return (0);
}
