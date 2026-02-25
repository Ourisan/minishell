#include "minishell.h"

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
	char *wrd;

	wrd = ft_substr("|", 0, 1);
	if (!wrd)
		return (0);
	token_add_back(token, token_new(wrd, TOKEN_PIPE));
	return (1);
}

int	handle_word(char *str, t_token **token)
{
	int		i;
	char	*wrd;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>' &&
			str[i] != '"' && str[i] != '\'' &&
			str[i] != ' ' && str[i] != '\t')
		i++;
	wrd = ft_substr(str, 0, i);
	if (!wrd)
		return (0);
	token_add_back(token, token_new(wrd, TOKEN_WORD));
	return (i);
}

int	handle_quote(char *str, t_token **token)
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
		return (perror("syntax error: quote not closed\n"), 0);
	wrd = ft_substr(str, 1, i - 1);
	if (!wrd)
		return (0);
	token_add_back(token, token_new(wrd, TOKEN_WORD));
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
