/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:17:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/19 15:54:25 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_token	*token;
	t_cmd	*cmds;
	t_shell	shell;

	(void)argc;
	(void)argv;
	rl = "";
	token = NULL;
	cmds = NULL;
	shell.env = env_init(envp);
	shell.last_status = 0;
	while (1)
	{
		rl = readline(shell_prompt(env_find(shell.env, "PWD")->value));
		if (rl && *rl)
			add_history(rl);
		else if (rl == NULL)
		{
			ft_printf("exit\n");
			rl_clear_history();
			exit(0);
		}
		if (!lexer(&token, rl, &shell))
			token_clear(&token);
		parser_init(&cmds, token);
		token_clear(&token);
		if (cmds)
			exec(cmds, &shell);
		cmds_clear(&cmds);
	}
	return (0);
}
