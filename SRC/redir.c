/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourisan <ourisan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 01:06:58 by ajuvin            #+#    #+#             */
/*   Updated: 2026/03/13 17:46:52 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_heredoc(t_redir *redir)
{
	char	*rl;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		rl = readline("heredoc> ");
		if (!rl)
			break ;
		if (strcmp(rl, redir->target) == 0)
		{
			free(rl);
			break ;
		}
		write(pipefd[1], rl, ft_strlen(rl));
		write(pipefd[1], "\n", 1);
			free(rl);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

void	redir_open(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
			redir->fd = open(redir->target, O_RDONLY);
		else if (redir->type == TOKEN_REDIR_OUT)
			redir->fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redir->type == TOKEN_APPEND)
			redir->fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (redir->type == TOKEN_HEREDOC)
			redir->fd = redir_heredoc(redir);
		if (redir->fd < 0)
		{
			perror(redir->target);
			exit(EXIT_FAILURE); ;
		}
		redir = redir->next;
	}
}

void	redir_exec(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
			dup2(redir->fd, STDIN_FILENO);
		else if (redir->type == TOKEN_APPEND || redir->type == TOKEN_REDIR_OUT)
			dup2(redir->fd, STDOUT_FILENO);
		close(redir->fd);
		redir = redir->next;
	}
}


