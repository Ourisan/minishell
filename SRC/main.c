/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:17:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/07 17:30:56 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cmd(char *cmd, char **argv, t_env *env)
{
	if (!cmd)
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(argv));
	if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd(argv, env));
	if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd, "export"))
		return (builtin_export(argv, env));
	if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset(argv, &env));
	if (!ft_strcmp(cmd, "env"))
		return (builtin_env(env));
	if (!ft_strcmp(cmd, "exit"))
		return (builtin_exit(argv));
	return (0);
}

int	is_builtin_cmd(char *cmd)
{
	if (!cmd)
		return (1);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
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
	while (1)
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
			if (is_builtin_cmd(cmds->argv[0]))
				builtin_cmd(cmds->argv[0], cmds->argv, env_list);
			else
			{
				// pid = fork();
				// if (pid == 0)
				// {
				// 	execve(path, args, env_list);
				// 	perror("execve");
				// 	exit(1);
				// }
				// waitpid(pid, &status, 0);
			}
		}
		cmds_clear(&cmds);
	}
	return (0);
}
