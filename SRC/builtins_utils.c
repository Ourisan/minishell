/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 01:02:55 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/05 02:09:35 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_expansion(char *var, t_env *env)
{
	char	*new_var;

	if (var[0] == '~')
		new_var = ft_strjoin(env_find(env, "HOME")->value, &var[1]);
	else
		return (var);
	return (new_var);
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
