/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourisan <ourisan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 07:51:40 by ajuvin            #+#    #+#             */
/*   Updated: 2026/04/04 07:54:46 by ourisan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*exec_path(char *cmd, t_env *env)
{
	int		i;
	char	**paths;
	char	*tmp;
	char	*path;

	i = -1;
	if (ft_strchr(cmd, '/'))
		return (cmd);
	paths = ft_split(env_find(env, "PATH")->value, ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(path, X_OK))
		{
			free_tab(paths);
			return (path);
		}
		free(path);
	}
	free_tab(paths);
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
