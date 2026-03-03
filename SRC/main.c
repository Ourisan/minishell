/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:17:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/02/23 19:16:00 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*rl;
	t_token *token;
	t_cmd	*cmds;

	rl = "";
	token = NULL;
	cmds = NULL;
	while ((ft_strncmp(rl, "exit", ft_strlen(rl)) || ft_strlen(rl) != 4)
			|| !ft_strlen(rl))
	{
		if (token)
			token_clear(&token);
		rl = readline("minishell$> ");
		if (rl && *rl)
			add_history(rl);
		if (!lexer(&token, rl))
			token_clear(&token);
		parser_init(&cmds, token);
		if (!cmds)
			return (1);
		cmds_clear(&cmds);
	}
	return (0);
}
