/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:17:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/04 16:50:20 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_token	*token;
	t_cmd	*cmds;
	t_env	*env_list;

	(void)argc;
	(void)argv;
	rl = "";
	token = NULL;
	cmds = NULL;
	env_list = env_init(envp);
	while (ft_strcmp(rl, "exit"))
	{
		if (token)
			token_clear(&token);
		rl = readline("minishell$> ");
		if (rl && *rl)
			add_history(rl);
		if (ft_strncmp(rl, "export", 6) == 0)
			builtin_export(ft_split(rl, ' '), env_list);
		if (!lexer(&token, rl))
			token_clear(&token);
		parser_init(&cmds, token);
		if (!cmds)
			return (1);
		cmds_clear(&cmds);
	}
	return (0);
}
