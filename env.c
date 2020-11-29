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

	if (!ft_strchr(env, '='))
		return (NULL);
	pos = (int)ft_strchr(env, '=') - (int)env;
	key = ft_strndup(env, pos);
	value = ft_strdup(env + pos + 1);
	return (create_env(key, value));
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
	if (!(g_env_head = malloc(sizeof(struct s_env))))
		return (1);
	g_env_head = create_env(NULL, NULL);
	while (env[++i])
		insert_last(create_env_str(env[i]));
	return (0);
}