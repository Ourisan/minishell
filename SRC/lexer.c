/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourisan <ourisan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 01:01:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/22 05:14:12 by ourisan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_op(char *str, t_token **token)
{
	int				i;
	char			*wrd;
	t_token_type	type;

	i = 0;
	if (str[i++] == '<')
	{
		if (str[i] != '<')
			type = TOKEN_REDIR_IN;
		else if (str[i++] == '<')
			type = TOKEN_HEREDOC;
	}
	else if (str[i - 1] == '>')
	{
		if (str[i] != '>')
			type = TOKEN_REDIR_OUT;
		else if (str[i++] == '>')
			type = TOKEN_APPEND;
	}
	wrd = ft_substr(str, 0, ++i);
	if (!wrd)
		return (0);
	token_add_back(token, token_new(wrd, type));
	return (i - 1);
}

int	handle_pipe(t_token **token)
{
	char	*wrd;

	wrd = ft_substr("|", 0, 1);
	if (!wrd)
		return (0);
	token_add_back(token, token_new(wrd, TOKEN_PIPE));
	return (1);
}

int	lexer(t_token **token, char *str, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = i;
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else if (str[i] == '<' || str[i] == '>')
			i += handle_op(&str[i], token);
		else if (str[i] == '|')
			i += handle_pipe(token);
		else
			i += handle_word(token, &str[i], shell);
		if (i <= j)
			return (0);
	}
	return (1);
}
