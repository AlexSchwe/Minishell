/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:46:44 by alexandre         #+#    #+#             */
/*   Updated: 2020/11/10 14:39:43 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <unistd.h>
# include <stdio.h>
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# define PIPE 1
# define NORMAL 0

int				g_status;

typedef	struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*previous;
	struct s_env	*next_alpha;
}				t_env;

t_env			*g_env_head;

/*
*** Une liste de mots. Type peut prendre la valeur ' ou "
*** Space prend la valeur 1 si un espace sépare ce mot du suivant
*/

typedef struct	s_parse
{
	char			*content;
	char			type;

	int				space;
	int				alias;
	int				prev;
	struct s_parse	*next;
	struct s_parse	*previous;
}				t_parse;

/*
*** Stocke les chaines d ecommande
*** Chacune contenant un pointeur vers t_parse
*/

typedef	struct	s_cmd
{
	struct s_parse	*head;
	struct s_cmd	*next;
	struct s_cmd	*previous;
	int				type;
	int				pipes[2];
}				t_cmd;

/*
*** builtin.c
*/

int				ft_pwd();

#endif
