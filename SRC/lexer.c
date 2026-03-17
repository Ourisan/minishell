/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 01:01:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/13 16:56:58 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_backslash(char *str, int i)
{
	int	count;

	count = 0;
	i--;
	while (str[i] == '\\' && i >= 0)
	{
		count++;
		i--;
	}
	return (count % 2);
}

char	*handle_backslash_no_quote(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			new_str[j++] = str[i + 1];
			i += 2;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*handle_backslash_double_quote(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			if (str[i + 1] == '"' || str[i + 1] == '\\' || str[i + 1] == '$')
			{
				new_str[j++] = str[i + 1];
				i += 2;
			}
			else
				new_str[j++] = str[i++];
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int	handle_op(char *str, t_token **token)
{
	int				i;
	char			*wrd;
	t_token_type	type;

	i = 0;
	if (str[i] == '<')
	{
		if (str[++i] == '<')
			type = TOKEN_HEREDOC;
		else
			type = TOKEN_REDIR_IN;
	}
	else if (str[i] == '>')
	{
		if (str[++i] == '>')
			type = TOKEN_APPEND;
		else
			type = TOKEN_REDIR_OUT;
	}
	wrd = ft_substr(str, 0, ++i);
	if (!wrd)
		return (0);
	token_add_back(token, token_new(wrd, type));
	return (i);
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

int	handle_word(char *str, t_token **token)
{
	int		i;
	char	*final_wrd;
	char	*wrd;

	i = 0;
	while (str[i] && !((str[i] == '<' || str[i] == '>'
		|| str[i] == '"' || str[i] == '\''
		|| str[i] == ' ' || str[i] == '\t') && !is_backslash(str, i)))
		i++;
	wrd = ft_substr(str, 0, i);
	if (!wrd)
		return (0);
	final_wrd = handle_backslash_no_quote(wrd);
	token_add_back(token, token_new(final_wrd, TOKEN_WORD));
	free(wrd);
	return (i);
}

int	handle_quote(char *str, t_token **token)
{
	int		i;
	char	*wrd;
	char	*final_wrd;
	char	quote;

	i = 0;
	quote = str[0];
	i++;
	while (str[i] && !(str[i] == quote
		&& ((quote == '"' && !is_backslash(str, i)) || quote == '\'')))
		i++;
	if (str[i] != quote)
		return (ft_printf_fd(2, "syntax error: quote not closed\n"), 0);
	wrd = ft_substr(str, 1, i - 1);
	if (!wrd)
		return (0);
	if (quote == '"')
		final_wrd = handle_backslash_double_quote(wrd);
	else
		final_wrd = wrd;
	token_add_back(token, token_new(final_wrd, TOKEN_WORD));
	free(wrd);
	return (i + 1);
}

int	lexer(t_token **token, char *str)
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
		else if (str[i] == '"' || str[i] == '\'')
			i += handle_quote(&str[i], token);
		else
			i += handle_word(&str[i], token);
		if (i <= j)
			return (0);
	}
	return (1);
}
