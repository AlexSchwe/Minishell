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

#ifndef MINISHELL_H
# define MINISHELL_H

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

int g_status;

typedef	struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env 	*previous;
	struct s_env	*next_alpha;
}				t_env;

t_env	*g_env_head;

/*
*** Une liste de mots. Type peut prendre la valeur ' ou "
*** Space prend la valeur 1 si un espace sépare ce mot du suivant
*/

typedef struct s_parse
{
	char *content;
	char type;

	int space;
	int alias;
	int prev;
	struct s_parse *next;
	struct s_parse *previous;
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

int 	ft_pwd();

void	ft_exit(t_parse *commands);

int		ft_check_built_in(t_parse *head);

/*
*** chevron.c
*/

int 	ft_stdin(int fd);

int 	alias_chevron(t_parse *parse);

int 	merge_after_chevron(t_parse *parse);

t_parse	*apply_chevron(t_parse *parse, int *error);

int 	ft_chevron(t_parse *head);

/*
*** echo.c
*/

t_parse	*ft_echo_n(t_parse *parse, int *n);

int	ft_echo(t_parse *parse);

/*
*** env.c
*/

int set_env(char **env);

int	ft_add_envv(char *command);

int insert_last(t_env *new);

t_env *create_env_str(char *str);

t_env *last(t_env *head);

/*
*** env_support.c
*/

char	*find_key(char *str);

t_env	*create_env(char *key, char *value);

int	ft_print_env();

int 	insert_env(t_env *first, t_env *new);

int 	delete_env(t_env *env);

/*
*** env_support2.c
*/

void ft_free_env();

t_env *find_env(char *key);

void export_env(char *key, char *value);

int len_env();

char *env_to_str(t_env *env);

char **array_env();

/*
*** support.c
*/

int ft_isspace(char c);

char *ft_strndup(char *str, int size);

int ft_free_vec(char **vec);

void 	print_vec(char **vec);

int is_semi_pipe(char *content);

/*
***ft_error.c
*/

int	ft_error(char *mess, char *mess2, int status);

int is_semi_pipe(char *str);

int is_redir(char *str);

int ft_syntax_error(t_parse *head);

/*
***export.c
*/

int ft_export(t_parse *parse);

int ft_export_error(t_env *env);

/*
*** export_p.c
*/

void ft_swap_alpha(t_env *preva, t_env *a, t_env *b);

void set_alpha();

int tri_env();

int 	export_p();

/*
*** ft_unset.c
*/

int	ft_unset(t_parse *cmds);

/*
*** ft_cd.c
*/

int		ft_cd(t_parse *cmds);

/*
*** main.c
*/

int	launch_cmd(t_parse *head);

int	minishell(char *line);

void	ft_prompt(void);

int		main(int argc, char **argv, char **env);

/*
***parse_exec.c
*/

int		parse_child(t_parse *parse);

int		ft_parse_path(char *exec, char **commands, char **dir);

int		ft_parse_exec(char *exec, char **commands, char **dir);

int		parse_child(t_parse *parse);

/*
*** parser.c
*/

int len_parse(t_parse *parse);

char **parse_to_char(t_parse *parse);

t_parse *create_parse(t_parse *current, char *content, int alias, int prev, int space);

void print_parser(t_parse *head);

t_parse *set_head_parser();

void	set_tail(char *str, int i, t_parse *current);

/*
***parser_support.c
*/

t_parse *delete_parser(t_parse *current);

int	free_parser(t_parse *head);

int merge_parse(t_parse *first, t_parse *second);

int merge_chevron(t_parse *head);


/*
***parser_support_2.c
*/

t_parse *ft_tail_parse(t_parse *head);

void 	insert_list(t_parse *parse, t_parse *head);

void 	cut_parser(t_parse *current);

t_parse *dup_parse(t_parse *parse);

t_parse *dup_list(t_parse *head);

/*
*** parsing.c
*/

t_parse	*set_parse_zero(char *begin, int i, t_parse *current);

t_parse *set_parse_redir(char *begin, int i, t_parse *current);

t_parse *set_parse_alias(char *begin, int i, t_parse *current);

t_parse *set_parse(char *begin, int i, t_parse *current);

t_parse *cmd_to_parser(char *str);

/*
*** pipe.c
*/

int redir_node(t_cmd *cmd, pid_t *pid, int i);

t_cmd *launch_pipe(t_cmd *current, pid_t *pid);

int	redir_cmds(t_cmd *head);

/*
*** replace.c
*/

int double_quote(t_parse *parse);

int apply_parse(t_parse *parse);

t_parse *alias_to_parser(char *str);

int 	apply_alias(t_parse *parse);

int ft_replace(t_parse *head);

/*
*** signal.c
*/

void	signal_set_up(void (*ft_handler)(int));

void	ft_handle_signal_child(int signum);

void	ft_handle_signal(int signum);

int		ft_eof(void);

/*
*** support2.c
*/

int		file_transfer(int fds, int fdd);

int 	merge_cmds(t_parse *head);

/*
*** t_cmd.c
*/

int	close_pipe_before(t_cmd *cmd);

int	close_pipe(t_cmd *head);

void print_list(t_cmd *head);

t_cmd *set_list(t_parse *head);

t_cmd *clean_list(t_cmd *head);

/*
*** t_cmd_support.c
*/

int 	len_pipe(t_cmd *head);

void	set_previous(t_cmd *head);

void 	free_cmd(t_cmd *head);

#endif
