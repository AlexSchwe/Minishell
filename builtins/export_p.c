#include "minishell.h"

void set_alpha()
{
	t_env *env;

	env = g_env_head;
	while (env)
	{
		env->next_alpha = env->next;
		env = env->next;
	}
}

void ft_swap_alpha(t_env *preva, t_env *a, t_env *b)
{

	if (preva)
		preva->next_alpha = b;
	a->next_alpha = b->next_alpha;
	b->next_alpha = a;
}

int tri_env(void)
{
	t_env *env;
	t_env *prev;

	set_alpha();
	prev = g_env_head;
	env = g_env_head->next_alpha;
	while (env && env->next_alpha)
	{
		if (ft_strcmp(env->key, env->next_alpha->key) > 0)
		{

			ft_swap_alpha(prev, env, env->next_alpha);
			prev = g_env_head;
			env = g_env_head->next_alpha;
		}
		else
		{
			prev = env;
			env = env->next_alpha;
		}
	}
	return (0);
}

int 	export_p()
{
	t_env *env;

	tri_env();
	env = g_env_head->next_alpha;
	while (env)
	{
		write(1, "declare -x ", ft_strlen("declare -x "));
		if (env->key)
		{
			write(1, env->key, ft_strlen(env->key));
			write(1, "=\"", 2);
		}
		if (env->value)
		{
			write(1, env->value, ft_strlen(env->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		env = env->next_alpha;
	}
	return (0);
}