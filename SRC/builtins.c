/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:39:35 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/05 02:08:52 by lde-plac         ###   ########.fr       */
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
	char	*path;
	char	new_path[PATH_MAX];
	t_env	*tmp;

	if (!args[1])
	{
		tmp = env_find(env, "HOME");
		if (!tmp || !tmp->value)
			return (ft_printf("cd: HOME not set\n"), 0);
		path = tmp->value;
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		tmp = env_find(env, "OLDPWD");
		if (!tmp || !tmp->value)
			return (ft_printf("cd: OLDPWD not set\n"), 0);
		path = ft_strdup(tmp->value);
		ft_printf("%s\n", path);
	}
	else
		path = var_expansion(args[1], env);
	tmp = env_find(env, "PWD");
	if (tmp && tmp->value)
		env_set(&env, "OLDPWD", tmp->value, 0);
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	if (getcwd(new_path, sizeof(new_path)))
		env_set(&env, "PWD", new_path, 0);
	return (0);
}

int	builtin_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)))
		ft_printf("%s\n", path);
	else
		perror("pwd");
	return (1);
}

int	builtin_export(char **args, t_env *env)
{
	int		i;
	int		error;
	char	*key;
	char	*value;

	i = 1;
	error = 0;
	if (!args[1])
	{
		while (env)
		{
			ft_printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
	else
	{
		while (args[i])
		{
			if (!is_valid_identifier(args[i]))
			{
				if (!error)
				{
					ft_printf("export: not an identifier: %s\n", args[i]);
					error = 1;
				}
			}
			else
			{
				if (ft_strnstr(args[i], "+=", ft_strlen(args[i])))
				{
					key = ft_strndup(args[i], ft_strnstr(args[i], "+=", ft_strlen(args[i])) - args[i]);
					value = ft_strdup(ft_strnstr(args[i], "+=", ft_strlen(args[i])) + 2);
					env_set(&env, key, value, 1);
					free(key);
					free(value);
				}
				else if (ft_strchr(args[i], '='))
				{
					key = ft_strndup(args[i], strchr(args[i], '=') - args[i]);
					value = ft_strdup(strchr(args[i], '=') + 1);
					env_set(&env, key, value, 0);
					free(key);
					free(value);
				}
				else if (!env_find(env, args[i]))
					env_set(&env, args[i], NULL, 0);
			}
			i++;
		}
	}
	return (error);
}
