#include "minishell.h"

int len_env()
{
	t_env *current;
	int i;

	i = 0;
	current = g_env_head->next;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char *env_to_str(t_env *env)
{
	char *tmp;
	char *dest;

	if (!env->key)
		return(NULL);
	tmp = ft_strjoin(env->key, "=");
	if (!env->value)
		return (tmp);
	dest = ft_strjoin(tmp, env->value);
	free(tmp);
	return (dest);
}

char **array_env()
{
	int i;
	char **dest;
	t_env *env;

	dest = malloc((len_env() + 1) * sizeof(char*));
	i = -1;
	env = g_env_head->next;
	while (++i < len_env())
	{
		dest[i] = env_to_str(env);
		env = env->next;
	}
	dest[i] = NULL;
	return (dest);
}

t_env *find_env(char *key)
{
	t_env *env;

	env = g_env_head->next;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
	}
	return (NULL);
}

void export_env(char *key, char *value)
{
	t_env *env;

	env = find_env(key);
	if (env)
	{
		free(env->value);
		env->value = value;
	}
	else
		env = create_env(key, value);
	insert_last(env);

}

void ft_free_env()
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