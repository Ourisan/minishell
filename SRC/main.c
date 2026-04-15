/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <ajuvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:17:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/04/15 14:14:31 by ajuvin           ###   ########.fr       */
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

void	main_loop(char*rl, t_token *token, t_cmd *cmds, t_shell *shell)
{
	shell->prompt = shell_prompt(env_find(shell->env, "PWD")->value);
	rl = readline(shell->prompt);
	if (rl && *rl)
		add_history(rl);
	else if (!rl)
	{
		ft_printf("exit\n");
		rl_clear_history();
		free_env(shell->env);
		free(shell->prompt);
		exit(0);
	}
	if (ft_strcmp(rl, ""))
	{
		if (!lexer(&token, rl, shell))
			token_clear(&token);
		parser_init(&cmds, token, shell);
		token_clear(&token);
		if (cmds)
			shell->last_status = exec(cmds, shell);
		cmds_clear(&cmds, shell->prompt);
	}
	else
		free(shell->prompt);
	free(rl);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_token	*token;
	t_cmd	*cmds;
	t_shell	shell;

	if (argc != 1)
	{
		ft_printf_fd(2, "Too many arguments");
		return (1);
	}
	(void)argv;
	rl = "";
	token = NULL;
	cmds = NULL;
	shell.env = env_init(envp);
	shell.last_status = 0;
	setup_shell_signals();
	while (1)
	{
		main_loop(rl, token, cmds, &shell);
	}
	return (0);
}
