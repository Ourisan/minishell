/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <ajuvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:58:45 by ajuvin            #+#    #+#             */
/*   Updated: 2026/04/15 16:09:21 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_cmd(t_cmd *cmds, t_shell *shell)
{
	char	*path;

	path = exec_path(cmds->argv[0], shell->env);
	if (!path)
	{
		ft_printf_fd(2, "%s: command not found\n", cmds->argv[0]);
		exit_child_process(cmds, shell, 127);
	}
	execve(path, cmds->argv, env_to_array(shell->env));
	if (errno == ENOENT)
		exit_child_process(cmds, shell, 127);
	if (errno == EACCES || errno == EISDIR)
		exit_child_process(cmds, shell, 126);
	exit_child_process(cmds, shell, 1);
}

void	child_process(t_cmd *cmds, t_shell *shell, int *pipefd, int prev_fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmds->next)
		dup2(pipefd[1], STDOUT_FILENO);
	close_pipe(pipefd);
	if (redir_open(cmds->redir))
		exit_child_process(cmds, shell, 1);
	redir_exec(cmds->redir);
	if (!cmds->argv || !cmds->argv[0])
		exit_child_process(cmds, shell, 0);
	if (is_builtin(cmds->argv[0]))
	{
		builtin_cmd(cmds, shell);
		exit_child_process(cmds, shell, 0);
	}
	child_cmd(cmds, shell);
}

void	pipe_exec(t_cmd *cmds, pid_t *pid_son, t_shell *shell, int *prev_fd)
{
	int		pipefd[2];

	pipefd[0] = -1;
	pipefd[1] = -1;
	if (cmds->next)
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe"));
	}
	*pid_son = fork();
	if ((*pid_son) < 0)
		return (perror("fork"));
	if ((*pid_son) == 0)
		child_process(cmds, shell, pipefd, *prev_fd);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmds->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	else
		close_pipe(pipefd);
}

int	exec_cmds(t_cmd *cmds)
{
	if ((!cmds->argv || !cmds->argv[0]) && redir_open(cmds->redir))
		return (1);
	if ((!cmds->argv || !cmds->argv[0]) && !cmds->next)
		return (0);
	if (!cmds->argv || !cmds->argv[0])
	{
		cmds = cmds->next;
		return (-1);
	}
	return (2);
}

int	exec(t_cmd *cmds, t_shell *shell)
{
	int		status;
	int		prev_fd;
	pid_t	pid_son;

	prev_fd = -1;
	if (cmds->argv && is_builtin(cmds->argv[0]) && !cmds->next && !cmds->redir)
		return (builtin_cmd(cmds, shell));
	while (cmds)
	{
		status = exec_cmds(cmds);
		if (status == 0 || status == 1)
			return (close_all_redirs(cmds->redir), status);
		else if (status == -1)
			continue ;
		pipe_exec(cmds, &pid_son, shell, &prev_fd);
		close_all_redirs(cmds->redir);
		cmds = cmds->next;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid_son, &status, 0);
	setup_shell_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		ft_printf("\n");
	return (WEXITSTATUS(status));
}
