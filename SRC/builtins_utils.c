/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 01:02:55 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/19 16:24:58 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_set(char *arg, t_env *env)
{
	char	*key;
	char	*value;

	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
	{
		key = ft_strndup(arg, ft_strnstr(arg, "+=", ft_strlen(arg)) - arg);
		value = ft_strdup(ft_strnstr(arg, "+=", ft_strlen(arg)) + 2);
		env_set(&env, key, value, 1);
		free(key);
		free(value);
	}
	else if (ft_strchr(arg, '='))
	{
		key = ft_strndup(arg, strchr(arg, '=') - arg);
		value = ft_strdup(strchr(arg, '=') + 1);
		env_set(&env, key, value, 0);
		free(key);
		free(value);
	}
	else if (!env_find(env, arg))
		env_set(&env, arg, NULL, 0);
}

void	export_env(char *arg, t_env *env, int *status)
{
	if (!is_valid_identifier(arg))
	{
		if (!(*status))
		{
			ft_printf_fd(2, "export: `%s': not a valid identifier\n", arg);
			*status = 1;
		}
	}
	else
		export_set(arg, env);
}

void	env_remove(char **args, t_env **env, int i)
{
	t_env	**cur;
	t_env	*tmp;

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

int	change_path(t_env *env, char *path)
{
	t_env	*tmp;
	char	new_path[PATH_MAX];

	tmp = env_find(env, "PWD");
	if (tmp && tmp->value)
		env_set(&env, "OLDPWD", tmp->value, 0);
	if (chdir(path) != 0)
	{
		ft_printf_fd(2, "cd: %s: No such file or directory\n", path);
		return (1);
	}
	if (getcwd(new_path, sizeof(new_path)))
		env_set(&env, "PWD", new_path, 0);
	return (0);
}

int	is_valid_identifier(const char *s)
{
	int	i;

	i = 0;
	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[++i] && s[i] != '=' && (s[i] != '+' || s[i + 1] != '='))
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
	}
	return (1);
}
