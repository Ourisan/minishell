/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:51:40 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/23 23:41:25 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return (1);
	if (tokens->type == TOKEN_PIPE)
	{
		ft_printf_fd(2, "syntax error: unexpected pipe\n");
		return (1);
	}
	tmp = tokens;
	while (tmp && tmp->next)
	{
		if (tmp->type == TOKEN_PIPE && tmp->next->type == TOKEN_PIPE)
		{
			ft_printf_fd(2, "syntax error: consecutive pipes\n");
			return (1);
		}
		tmp = tmp->next;
	}
	if (tmp && tmp->type == TOKEN_PIPE)
	{
		ft_printf_fd(2, "syntax error: unexpected pipe at end\n");
		return (1);
	}
	return (0);
}

int	check_redir(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT
			|| tmp->type == TOKEN_APPEND)
		{
			if (!tmp->next || tmp->next->type != TOKEN_WORD)
			{
				ft_printf_fd(2, "syntax error: missing target for redirection");
				ft_printf_fd(2, "\n");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_heredoc(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
		{
			if (!tmp->next || tmp->next->type != TOKEN_WORD)
			{
				ft_printf_fd(2, "syntax error: heredoc missing delimiter\n");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_cmd(t_token *tokens)
{
	if (check_pipe(tokens))
		return (1);
	if (check_redir(tokens))
		return (1);
	if (check_heredoc(tokens))
		return (1);
	return (0);
}
