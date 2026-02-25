/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:39:35 by lde-plac          #+#    #+#             */
/*   Updated: 2026/02/25 19:39:31 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **args)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	i = 1;
	while (args[i] && args[i][0] == '-' && args[i][1])
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		flag = 1;
		i++;
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
	return (1);
}

int	builtin_cd(char **args, t_env *env)
{
	int		i;
	char	*path;
	char	*old_path;

	i = 0;
	if (!args[1])
	{
		path = env_find(env, "HOME")->value;
		if (!path)
			return (ft_printf("cd: HOME not set\n"), 0);
	}
	else if (ft_strncmp(args[1], "-", ft_strlen(args[1])) == 0)
	{
		path = env_find(env, "OLDPWD")->value;
		if (!path)
			return (ft_printf("cd: OLDPWD not set\n"), 0);
	}
	else
		path = args[1];
	old_path = env_find(env, "PWD")->value;
	if (old_path)
		env_set(env, "OLDPWD", old_path);
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	return (0);
}

int	builtin_pwd(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)))
		ft_printf("%s\n", path);
	else
		perror("pwd");
	return (1);
}
