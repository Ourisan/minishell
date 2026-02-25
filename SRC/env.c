/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:29:34 by lde-plac          #+#    #+#             */
/*   Updated: 2026/02/25 19:36:11 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add_back(t_env **env, t_env *new)
{
	t_env *last;
	if (!*env)
	{
		*env = new;
		return;
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_env	*env_new(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = NULL;
	return (env);
}

t_env	*env_find(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return env;
		env = env->next;
	}
	return NULL;
}

void	env_set(t_env *env, char *key, char *value)
{
	t_env *e;

	e = env_find(env, key);
	if (e)
	{
		free(e->value);
		e->value = value;
	}
	else
		env_add_back(&env, env_new(key, value));
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	int		i;
	char	*key;
	char	*value;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		key = ft_strndup(envp[i], strchr(envp[i], '=') - envp[i]);
		value = ft_strdup(strchr(envp[i], '=') + 1);
		env_add_back(&env, env_new(key, value));
		free(key);
		free(value);
		i++;
	}
	return (env);
}
