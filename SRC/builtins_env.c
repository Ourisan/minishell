/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 22:56:37 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/13 00:27:55 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(char **args, t_env *env)
{
	int		i;
	int		status;

	i = 1;
	status = 0;
	if (!args[1])
	{
		while (env)
		{
			ft_printf("declare -x %s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
	else
	{
		while (args[i])
		{
			export_env(args[i], env, &status);
			i++;
		}
	}
	return (status);
}

int	builtin_unset(char **args, t_env **env)
{
	int		i;
	int		status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_printf_fd(2, "unset: `%s': not a valid identifier\n", args[i]);
			status = 1;
		}
		else
			env_remove(args, env, i);
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
