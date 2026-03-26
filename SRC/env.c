/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:29:34 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/26 18:05:01 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env	*env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		free(env->key);
		free(env->value);
		env = env->next;
		free(tmp);
	}
}

void	env_add_back(t_env **env, char *key, char *value)
{
	t_env	*last;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!env)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_env	*env_find(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	env_set(t_env **env, char *key, char *value, int append)
{
	t_env	*e;
	char	*new_value;

	e = env_find(*env, key);
	if (e)
	{
		if (append)
			new_value = ft_strjoin(e->value, value);
		else
			new_value = value;
		free(e->value);
		e->value = ft_strdup(new_value);
	}
	else
		env_add_back(env, key, value);
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
		env_add_back(&env, key, value);
		free(key);
		free(value);
		i++;
	}
	return (env);
}
