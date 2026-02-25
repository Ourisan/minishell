/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:17:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/02/25 19:09:03 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_token *token;
	t_env	*env_list;

	(void)argc;
	(void)argv;
	rl = "";
	token = NULL;
	env_list = env_init(envp);
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
	}
	return (0);
}
