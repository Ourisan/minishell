/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourisan <ourisan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:17:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/11 20:08:32 by ourisan          ###   ########.fr       */
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
	while (1)
	{
		rl = readline(shell_prompt(env_find(env_list, "PWD")->value));
		if (rl && *rl)
			add_history(rl);
		if (!lexer(&token, rl))
			token_clear(&token);
		parser_init(&cmds, token);
		token_clear(&token);
		if (cmds)
			executor(cmds, env_list);
		cmds_clear(&cmds);
	}
	return (0);
}
