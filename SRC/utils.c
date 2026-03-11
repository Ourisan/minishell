/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourisan <ourisan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 01:55:23 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/11 18:47:24 by ourisan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_env *env)
{
	int		i;
	int		len;
	t_env	*head;
	char	**env_a;

	i = 0;
	len = 0;
	head = env;
	while (env)
	{
		len++;
		env = env->next;
	}
	env_a = (char **)malloc((len + 1) * sizeof(char *));
	env = head;
	while (i < len)
	{
		env_a[i] = ft_strjoin(ft_strjoin(env->key, "="), env->value);
		env = env->next;
		i++;
	}
	env_a[i] = NULL;
	return (env_a);
}

char	*exec_path(char	*cmd, t_env *env)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (cmd);
	paths = ft_split(env_find(env, "PATH")->value, ':');
	while (paths[i])
	{
		path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (!access(path, X_OK))
			return (path);
		i++;
	}
	return (NULL);
}

char	*shell_prompt(char *pwd)
{
	char	*prompt;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			j = i;
		i++;
	}
	prompt = ft_strjoin(&pwd[j + 1], "$> ");
	return (prompt);
}
