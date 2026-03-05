/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 01:55:23 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/05 01:59:30 by lde-plac         ###   ########.fr       */
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
