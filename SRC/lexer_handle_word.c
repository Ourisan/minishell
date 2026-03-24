/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourisan <ourisan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 23:41:40 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/24 19:36:18 by ourisan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_no_quote(char **arg, char *str, t_shell *shell)
{
	int		i;
	char	*wrd;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>'
		&& str[i] != '"' && str[i] != '\'' && str[i] != '|'
		&& str[i] != ' ' && str[i] != '\t')
		i++;
	wrd = ft_substr(str, 0, i);
	if (!wrd)
		return (-1);
	wrd = var_expansion(wrd, shell);
	*arg = ft_strjoin(*arg, wrd);
	return (i);
}

int	handle_quote(char **arg, char *str, t_shell *shell)
{
	int		i;
	char	*wrd;
	char	quote;

	i = 0;
	quote = str[0];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] != quote)
		return (ft_printf_fd(2, "syntax error: quote not closed\n"), -1);
	wrd = ft_substr(str, 1, i - 1);
	if (!wrd)
		return (-1);
	if (quote != '\'')
		wrd = var_expansion(wrd, shell);
	*arg = ft_strjoin(*arg, wrd);
	return (i + 1);
}

int	handle_word_loop(char **wrd, char *str, t_shell *shell)
{
	int	j;

	if (*str == '\'' || *str == '"')
		j = handle_quote(wrd, str, shell);
	else
		j = handle_no_quote(wrd, str, shell);
	return (j);
}

int	handle_word(t_token **token, char *str, t_shell *shell)
{
	int		i;
	int		j;
	char	*wrd;

	i = 0;
	wrd = ft_strdup("");
	while (str[i] && str[i] != '<' && str[i] != '>'
		&& str[i] != '|' && str[i] != ' ' && str[i] != '\t')
	{
		j = handle_word_loop(&wrd, &str[i], shell);
		if (j < 0)
			return (-1);
		i += j;
	}
	if (!wrd)
		return (0);
	token_add_back(token, token_new(wrd, TOKEN_WORD));
	return (i);
}
