/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:39:35 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/19 16:28:23 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **args)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	i = 0;
	while (args[++i] && args[i][0] == '-' && args[i][1])
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		flag = 1;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!flag)
		ft_printf("\n");
	return (0);
}

int	builtin_cd(char **args, t_env *env)
{
	char	*path;
	t_env	*tmp;

	if (args[2])
		return (ft_printf_fd(2, "cd: too many arguments\n"), 1);
	if (!args[1])
	{
		tmp = env_find(env, "HOME");
		if (!tmp || !tmp->value)
			return (ft_printf_fd(2, "cd: HOME not set\n"), 1);
		path = tmp->value;
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		tmp = env_find(env, "OLDPWD");
		if (!tmp || !tmp->value)
			return (ft_printf_fd(2, "cd: OLDPWD not set\n"), 1);
		path = ft_strdup(tmp->value);
		ft_printf("%s\n", path);
	}
	else
		path = args[1];
	return (change_path(env, path));
}

int	builtin_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)))
		ft_printf("%s\n", path);
	else
		return (perror("pwd"), 1);
	return (0);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int		i;

	printf("exit\n");
	if (!args[1])
		exit(shell->last_status);
	i = 0;
	while (args[1][i])
	{
		if (args[1][i] < '0' || args[1][i] > '9')
		{
			ft_printf_fd(2, "exit: %s: numeric argument required\n", args[1]);
			exit(255);
		}
		i++;
	}
	if (args[2])
	{
		ft_printf_fd(2, "exit: too many arguments\n");
		return (1);
	}
	exit((int)(ft_atol(args[1]) % 256));
}
