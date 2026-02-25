/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:39:35 by lde-plac          #+#    #+#             */
/*   Updated: 2026/02/25 15:51:28 by lde-plac         ###   ########.fr       */
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
			break;
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

int	builtin_pwd(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)))
		ft_printf("%s\n", path);
	else
		perror("pwd");
	return (1);
}
