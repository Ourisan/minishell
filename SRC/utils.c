/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 01:55:23 by lde-plac          #+#    #+#             */
/*   Updated: 2026/04/13 12:15:20 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_prompt(char *pwd)
{
	char	*prompt;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			j = i;
		i++;
	}
	prompt = ft_strjoin(&pwd[j + 1], "$> ");
	return (prompt);
}

void	expand_var_2(char **new_var, t_shell *shell, int i, int j)
{
	char	*l;
	char	*r;
	char	*tmp_var;
	char	*tmp_var_2;
	t_env	*tmp;

	l = ft_strndup((*new_var), i);
	r = ft_strdup(&(*new_var)[j]);
	tmp_var = ft_strndup(&(*new_var)[i + 1], j - i - 1);
	tmp = env_find(shell->env, tmp_var);
	free(tmp_var);
	if (tmp)
	{
		tmp_var_2 = ft_strjoin(tmp->value, r);
		tmp_var = ft_strjoin(l, tmp_var_2);
		free(tmp_var_2);
	}
	else
		tmp_var = ft_strdup("");
	free(*new_var);
	*new_var = tmp_var;
	free(l);
	free(r);
}

void	expand_var(char **new_var, t_shell *shell, int i, int j)
{
	char	*l;
	char	*r;
	char	*tmp_var;
	char	*tmp_var_2;

	if ((*new_var)[i + 1] == '?')
	{
		l = ft_strndup((*new_var), i);
		r = ft_strdup(&(*new_var)[i + 2]);
		tmp_var_2 = ft_strjoin(ft_itoa(shell->last_status), r);
		tmp_var = ft_strjoin(l, tmp_var_2);
		free(*new_var);
		*new_var = tmp_var;
		free(tmp_var_2);
		free(l);
		free(r);
	}
	else
	{
		while ((*new_var)[j] && (*new_var)[j] != '/' && (*new_var)[j] != ' '
			&& (*new_var)[j] != '$')
			j++;
		expand_var_2(new_var, shell, i, j);
	}
}

char	*var_expansion(char *var, t_shell *shell)
{
	int		i;
	char	*home;
	char	*new_var;

	i = 0;
	if (var[0] != '~' && !ft_strchr(var, '$'))
		return (var);
	new_var = ft_strdup(var);
	free(var);
	while (new_var[i])
	{
		if (i == 0 && new_var[i] == '~')
		{
			home = env_find(shell->env, "HOME")->value;
			new_var = ft_strjoin(home, &new_var[1]);
		}
		if (new_var[i] == '$' && new_var[i + 1]
			&& new_var[i + 1] != ' ')
		{
			expand_var(&new_var, shell, i, i + 1);
		}
		i++;
	}
	return (new_var);
}

char	**env_to_array(t_env *env)
{
	int		i;
	int		len;
	t_env	*head;
	char	**env_a;

	i = 0;
	len = 0;
	head = env;
	while (env)
	{
		len++;
		env = env->next;
	}
	env_a = (char **)malloc((len + 1) * sizeof(char *));
	env = head;
	while (i < len)
	{
		env_a[i] = ft_strjoin(ft_strjoin(env->key, "="), env->value);
		env = env->next;
		i++;
	}
	env_a[i] = NULL;
	return (env_a);
}
