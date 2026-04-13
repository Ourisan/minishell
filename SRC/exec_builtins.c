/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:20:55 by lde-plac          #+#    #+#             */
/*   Updated: 2026/04/13 12:22:14 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cmd(t_cmd *cmds, t_shell *shell)
{
	if (!cmds || !cmds->argv[0])
		return (1);
	if (!ft_strcmp(cmds->argv[0], "echo"))
		return (builtin_echo(cmds->argv));
	if (!ft_strcmp(cmds->argv[0], "cd"))
		return (builtin_cd(cmds->argv, shell->env));
	if (!ft_strcmp(cmds->argv[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmds->argv[0], "export"))
		return (builtin_export(cmds->argv, shell->env));
	if (!ft_strcmp(cmds->argv[0], "unset"))
		return (builtin_unset(cmds->argv, &shell->env));
	if (!ft_strcmp(cmds->argv[0], "env"))
		return (builtin_env(shell->env));
	if (!ft_strcmp(cmds->argv[0], "exit"))
		return (builtin_exit(cmds, shell));
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
