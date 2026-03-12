/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:58:45 by ajuvin            #+#    #+#             */
/*   Updated: 2026/03/12 18:03:34 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cmd(char *cmd, char **argv, t_shell *shell)
{
	if (!cmd)
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(argv));
	if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd(argv, shell->env));
	if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd, "export"))
		return (builtin_export(argv, shell->env));
	if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset(argv, &shell->env));
	if (!ft_strcmp(cmd, "env"))
		return (builtin_env(shell->env));
	if (!ft_strcmp(cmd, "exit"))
		return (builtin_exit(argv, shell));
	return (0);
}

int	is_builtin_cmd(char *cmd)
{
	if (!cmd)
		return (1);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

void	child_process(t_cmd *cmds, t_shell *shell, int *pipefd, int prev_fd)
{
	char	*path;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmds->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	redir(cmds->redir);
	if (is_builtin_cmd(cmds->argv[0]))
	{
		builtin_cmd(cmds->argv[0], cmds->argv, shell);
		exit(1);
	}
	path = exec_path(cmds->argv[0], shell->env);
	if (path)
	{
		execve(path, cmds->argv, env_to_array(shell->env));
		perror("execve");
		exit(1);
	}
	else
	{
		ft_printf_fd(2, "%s: command not found\n", cmds->argv[0]);
		exit(1);
	}
}

void	pipe_executor(t_cmd *cmds, t_shell *shell)
{
	int		pipefd[2];
	int		prev_fd;
	int		status;
	pid_t	pid_son;

	prev_fd = -1;
	while (cmds)
	{
		if (cmds->next)
		{
			if (pipe(pipefd) == -1)
				return (perror("pipe"));
		}
		pid_son = fork();
		if (pid_son < 0)
			return (perror("fork"));
		if (pid_son == 0)
			child_process(cmds, shell, pipefd, prev_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmds = cmds->next;
	}
	waitpid(pid_son, &status, 0);
	shell->last_status = WEXITSTATUS(status);
}

void	executor(t_cmd *cmds, t_shell *shell)
{
	if (!cmds || !cmds->argv || !cmds->argv[0])
		return ;
	if (is_builtin_cmd(cmds->argv[0]) && !cmds->next && !cmds->redir)
	{
		shell->last_status = builtin_cmd(cmds->argv[0], cmds->argv, shell);
		return ;
	}
	pipe_executor(cmds, shell);
}
