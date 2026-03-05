/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:17:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/05 02:00:44 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cmd(char *cmd, char **argv, t_env *env)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(argv), 0);
	if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd(argv, env), 0);
	if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd(), 0);
	if (!ft_strcmp(cmd, "export"))
		return (builtin_export(argv, env), 0);
	return (1);
}

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
		rl = readline(shell_prompt(env_find(env_list, "PWD")->value));
		if (rl && *rl)
			add_history(rl);
		if (!lexer(&token, rl))
			token_clear(&token);
		parser_init(&cmds, token);
		if (cmds)
		{
			if (!builtin_cmd(cmds->argv[0], cmds->argv, env_list))
			{
			}
		}
		cmds_clear(&cmds);
	}
	return (0);
}
