/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 15:50:36 by lde-plac          #+#    #+#             */
/*   Updated: 2026/04/13 12:21:57 by lde-plac         ###   ########.fr       */
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

void	exit_child_process(t_cmd *cmds, t_shell *shell, int code)
{
	cmds_clear(&cmds, shell->prompt);
	free_env(shell->env);
	exit(code);
}

void	close_pipe(int *pipefd)
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}
