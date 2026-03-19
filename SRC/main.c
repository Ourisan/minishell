/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:17:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/19 17:36:49 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_shell_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

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
	setup_shell_signals();
	while (1)
	{
		rl = readline(shell_prompt(env_find(shell.env, "PWD")->value));
		if (rl && *rl)
			add_history(rl);
		else if (!rl)
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
