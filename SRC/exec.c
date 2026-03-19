/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:58:45 by ajuvin            #+#    #+#             */
/*   Updated: 2026/03/19 16:53:37 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_cmd(t_cmd *cmds, t_shell *shell)
{
	char	*path;

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

void	child_process(t_cmd *cmds, t_shell *shell, int *pipefd, int prev_fd)
{
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
	redir_exec(cmds->redir);
	child_cmd(cmds, shell);
}

void	pipe_exec(t_cmd *cmds, pid_t pid_son, t_shell *shell)
{
	int		prev_fd;
	int		pipefd[2];

	prev_fd = -1;
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
}

void	exec(t_cmd *cmds, t_shell *shell)
{
	int		status;
	pid_t	pid_son;

	if (!cmds || !cmds->argv || !cmds->argv[0])
		return ;
	if (is_builtin_cmd(cmds->argv[0]) && !cmds->next && !cmds->redir)
	{
		shell->last_status = builtin_cmd(cmds->argv[0], cmds->argv, shell);
		return ;
	}
	while (cmds)
	{
		redir_open(cmds->redir);
		pipe_exec(cmds, pid_son, shell);
		cmds = cmds->next;
	}
	waitpid(pid_son, &status, 0);
	shell->last_status = WEXITSTATUS(status);
}
