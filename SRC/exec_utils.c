/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 15:50:36 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/19 15:50:57 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cmd(char *cmd, char **argv, t_shell *shell)
{
	if (!cmd)
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(argv));
	if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd(argv, shell->env));
	if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd, "export"))
		return (builtin_export(argv, shell->env));
	if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset(argv, &shell->env));
	if (!ft_strcmp(cmd, "env"))
		return (builtin_env(shell->env));
	if (!ft_strcmp(cmd, "exit"))
		return (builtin_exit(argv, shell));
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
