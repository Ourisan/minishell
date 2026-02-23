/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:17:04 by lde-plac          #+#    #+#             */
/*   Updated: 2026/02/23 19:16:00 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*rl;

	rl = "";
	while ((ft_strncmp(rl, "exit", ft_strlen(rl)) || ft_strlen(rl) != 4)
			|| !ft_strlen(rl))
	{
		rl = readline("minishell$> ");
		if (rl && *rl)
			add_history(rl);
	}
	return (0);
}
