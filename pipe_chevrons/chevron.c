#include "minishell.h"

/*
*** Remplace stdin par le contenu du fichier donné en argument
*/

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
	char *value;
	t_parse *new;
	int len;

	value = find_key(parse->content + 1);
	if (!value)
		return (1);
	free(parse->content);
	parse->content = ft_strdup(value);
	new = alias_to_parser(value);
	len = len_parse(new);
	free_parser(new);
	if (len != 1 && !parse->type)
		return (1);
	parse->alias = 0;
	return (0);
}

/*
*** gère les alias immédiatemment après les chevrons
*/

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

/*
*** ouvre les fichiers concernés
*** redirige stdout ou bien renvoie vers stdin
*/

t_parse *apply_chevron(t_parse *parse, int *error)
{
	int fd;
	char *file;

	if (merge_after_chevron(parse->next))
	{
		*error = !ft_error(parse->content, "ambiguous redir", 1);
		return (NULL);
	}
	file = parse->next->content;
	if (!ft_strcmp(parse->content, ">>"))
		fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (!ft_strcmp(parse->content, ">"))
		fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (!ft_strcmp(parse->content, "<"))
		fd = open(file, O_RDONLY);
	if (fd == -1 && !ft_error(file, strerror(errno), 1) && (*error = 1))
		return (NULL);
	if (!ft_strcmp(parse->content, ">") || !ft_strcmp(parse->content, ">>"))
		if ((dup2(fd, STDOUT_FILENO)) == -1)
			*error = !ft_error(file, strerror(errno), 1);
	if (!ft_strcmp(parse->content, "<"))
		*error = ft_stdin(fd);
	return (parse);
}

/*
*** redirige stdin ou stdout
*** supprime les commandes concernées
*** détecte les erreur
*/

int 	ft_chevron(t_parse *head)
{
	t_parse *current;
	current = head->next;
	int error;

	error = 0;
	while (current)
	{
		if (current->content && is_redir(current->content) && !current->type)
		{
			current = apply_chevron(current, &error);
			current = delete_parser(current);
			current = delete_parser(current);
		}
		else
			current = current->next;
		if (error)
			return (1);
	}
	return (0);
}