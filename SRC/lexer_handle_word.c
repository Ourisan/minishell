
#include "minishell.h"

int	handle_no_quote(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '<' && str[i] != '>'
		&& str[i] != '"' && str[i] != '\'' && str[i] != '|'
		&& str[i] != ' ' && str[i] != '\t')
		i++;
	return (i);
}

int	handle_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = str[0];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] != quote)
		return (ft_printf_fd(2, "syntax error: quote not closed\n"), 0);
	return (i + 1);
}

int	handle_word_loop(char **wrd, char *str, t_shell *shell)
{
	int		j;

	if (*str == '\'' || *str == '"')
	{
		j = handle_quote(str);
		*wrd = ft_strjoin(*wrd, ft_substr(str, 1, j - 2));
		if (*str != '\'')
			*wrd = var_expansion(*wrd, shell);
	}
	else
	{
		j = handle_no_quote(str);
		*wrd = var_expansion(ft_strjoin(*wrd, ft_substr(str, 0, j)), shell);
	}
	return (j);
}

int	handle_word(t_token **token, char *str, t_shell *shell)
{
	int		i;
	char	*wrd;

	i = 0;
	wrd = "";
	while (str[i] && str[i] != '<' && str[i] != '>'
		&& str[i] != '|' && str[i] != ' ' && str[i] != '\t')
		i += handle_word_loop(&wrd, &str[i], shell);
	if (!wrd)
		return (0);
	token_add_back(token, token_new(wrd, TOKEN_WORD));
	return (i);
}