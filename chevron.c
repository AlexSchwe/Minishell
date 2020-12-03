#include "minishell.h"

int ft_stdin(int fd)
{
	int		pip[2];

	pipe(pip);
	if ((dup2(pip[0], STDIN_FILENO)) == -1)
		return(1);

	if (close(pip[0]))
		return (1);
	if (file_transfer(fd, pip[1]))
		return (1);
	if (close(pip[1]))
		return(1);
	return (0);
}

int alias_chevron(t_parse *parse)
{
	apply_alias(parse);
	if (len_parse(parse) != 1)
		return (!free_parser(parse));
	free(parse->content);
	parse->alias = 0;
	free_parser(parse);
	return (0);
}

int merge_after_chevron(t_parse *parse)
{
	if (!parse)
		return (0);
	if (parse->alias && alias_chevron(parse))
		return (1);
	while (!parse->space && parse->next)
	{
		if (parse->next->alias)
			if (alias_chevron(parse->next))
				return (1);		
		merge_parse(parse, parse->next);
	}
	return (0);
}

t_parse *apply_chevron(t_parse *parse, int *error)
{
	int fd;

	if (merge_after_chevron(parse->next))
		*error = !ft_error(parse->content, "ambiguous redir", 1);
	if (!ft_strcmp(parse->content, ">>"))
		fd = open(parse->content, O_CREAT | O_APPEND);
	if (!ft_strcmp(parse->content, ">"))
		fd = open(parse->content, O_CREAT | O_TRUNC);
	if (!ft_strcmp(parse->content, "<"))
		fd = open(parse->content, O_RDONLY);
	if (fd == -1)
		*error = !ft_error(parse->content, strerror(errno), 1);
	if (!ft_strcmp(parse->content, ">") || !ft_strcmp(parse->content, ">>"))
		if ((*error =  dup2(fd, STDOUT_FILENO)))
			ft_error(">", strerror(errno), 1);
	if (!ft_strcmp(parse->content, "<"))
		*error = ft_stdin(fd);
	parse = delete_parser(parse);
	parse = delete_parser(parse);
	return (parse);
}

/*
***redirige stdin ou stdout
*** supprime les commandes concernées
*** détecte les erreur
*/

int 	ft_chevron(t_parse *head)
{
	t_parse *current;
	current = head;
	int error;

	error = 0;
	while (current)
	{
		if (current->content && is_redir(current->content))
			current = apply_chevron(current, &error);
		else
			current = current->next;
		if (error)
			return (1);
	}
	return (0);
}