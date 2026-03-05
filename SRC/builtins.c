/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:39:35 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/05 18:55:25 by lde-plac         ###   ########.fr       */
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
	return (0);
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
		path = var_expansion(args[1], env);
	tmp = env_find(env, "PWD");
	if (tmp && tmp->value)
		env_set(&env, "OLDPWD", tmp->value, 0);
	if (chdir(path) != 0)
		return (ft_printf_fd(2, "cd: %s: No such file or directory\n", path), 1);
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
		return (perror("pwd"), 1);
	return (0);
}

int	builtin_export(char **args, t_env *env)
{
	int		i;
	int		status;
	char	*key;
	char	*value;

	i = 1;
	status = 0;
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
				if (!status)
				{
					ft_printf_fd(2, "export: not an identifier: %s\n", args[i]);
					status = 1;
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
	return (status);
}

int	builtin_unset(char **args, t_env **env)
{
	int		i;
	int		status;
	t_env	**cur;
	t_env	*tmp;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_printf_fd(2, "minishell: unset: `%s': not a valid identifier\n", args[i]);
			status = 1;
		}
		else
		{
			cur = env;
			while (*cur)
			{
				if (!ft_strcmp((*cur)->key, args[i]))
				{
					tmp = *cur;
					*cur = (*cur)->next;
					free(tmp->key);
					free(tmp->value);
					free(tmp);
				}
				else
					cur = &(*cur)->next;
			}
		}
		i++;
	}
	return (status);
}

int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	builtin_exit(char **args)
{
	int		i;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (args[2])
	{
		ft_printf_fd(2, "exit: too many arguments\n");
		return (1);
	}
	i = 0;
	while (args[1][i])
	{
		if (args[1][i] < '0' || args[1][i] > '9')
		{
			ft_printf_fd(2, "exit: %c: numeric argument required\n", args[1][i]);
			exit(255);
		}
		i++;
	}
	exit((int)(ft_atol(args[1]) % 256));
}
