/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourisan <ourisan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 01:06:58 by ajuvin            #+#    #+#             */
/*   Updated: 2026/04/04 04:55:13 by ourisan          ###   ########.fr       */
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

int	redir_open(t_redir *r)
{
	while (r)
	{
		if (r->type == TOKEN_REDIR_IN)
			r->fd = open(r->target, O_RDONLY);
		else if (r->type == TOKEN_REDIR_OUT)
			r->fd = open(r->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (r->type == TOKEN_APPEND)
			r->fd = open(r->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (r->fd < 0)
		{
			perror(r->target);
			return (1);
		}
		r = r->next;
	}
	return (0);
}

void	redir_open_heredoc(t_redir *r)
{
	while (r)
	{
		if (r->type == TOKEN_HEREDOC)
			r->fd = redir_heredoc(r);
		else
			return ;
		if (r->fd < 0)
		{
			perror(r->target);
			exit(EXIT_FAILURE);
		}
		r = r->next;
	}
}

void	redir_exec(t_redir *r)
{
	while (r)
	{
		if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC)
			dup2(r->fd, STDIN_FILENO);
		else if (r->type == TOKEN_APPEND || r->type == TOKEN_REDIR_OUT)
			dup2(r->fd, STDOUT_FILENO);
		close(r->fd);
		r = r->next;
	}
}

void	close_all_redirs(t_redir *r)
{
	while (r)
	{
		if (r->fd > 2)
			close(r->fd);
		r = r->next;
	}
}
