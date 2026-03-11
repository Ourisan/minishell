/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourisan <ourisan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 01:06:58 by ajuvin            #+#    #+#             */
/*   Updated: 2026/03/11 18:57:44 by ourisan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in_out(t_redir *redir)
{
	int	fd;

	if (redir->type == TOKEN_REDIR_IN)
	{
		fd = open(redir->target, O_RDONLY);
		if (fd < 0)
			return ;
		dup2(fd, STDIN_FILENO);
	}
	else if (redir->type == TOKEN_REDIR_OUT)
	{
		fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return ;
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
}

void	redir_append(t_redir *redir)
{
	int	fd;

	if (redir->type == TOKEN_APPEND)
	{
		fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return ;
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
}

void	redir_heredoc(t_redir *redir)
{
	char	*rl;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return ;
	rl = "";
	while (strcmp(rl, redir->target) != 0)
	{
		rl = readline("heredoc>");
		write(pipefd[1], rl, ft_strlen(rl));
		write(pipefd[1], "\n", 1);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_REDIR_OUT)
			redir_in_out(redir);
		else if (redir->type == TOKEN_APPEND)
			redir_append(redir);
		else if (redir->type == TOKEN_HEREDOC)
			redir_heredoc(redir);
		redir = redir->next;
	}
}
