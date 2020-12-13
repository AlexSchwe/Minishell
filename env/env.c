#include "minishell.h"

t_env *last(t_env *head)
{
	t_env *next;

	next = head;
	while (next && next->next)
		next = next->next;
	return (next);
}

t_env *create_env_str(char *env)
{
	int pos;
	char *key;
	char *value;
	t_env *dest;

	if (!ft_strchr(env, '='))
		return (NULL);
	pos = (long)ft_strchr(env, '=') - (long)env;
	key = ft_strndup(env, pos);
	value = ft_strdup(env + pos + 1);
	dest = create_env(key, value);
	free(key);
	free(value);
	return (dest);
}

int insert_last(t_env *new)
{
	return (insert_env(last(g_env_head), new));
}
/*
**ajoute une variable d'environnement
*/

int	ft_add_envv(char *command)
{
	t_env *new;

	new = create_env_str(command);

	if (!new)
		return (1);
	return (insert_last(new));
}

int set_env(char **env)
{
	int i;

	i = -1;
	if (!(g_env_head = create_env(NULL, NULL)))
		return (1);
	while (env[++i])
		insert_last(create_env_str(env[i]));
	return (0);
}