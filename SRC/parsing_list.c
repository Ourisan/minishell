/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:51:34 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/04 16:51:35 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	argv_add(char ***argv, char *value)
{
	int		i;
	char	**new;

	i = 0;
	if (!*argv)
	{
		*argv = malloc(2 * sizeof(char *));
		(*argv)[0] = ft_strdup(value);
		(*argv)[1] = NULL;
		return ;
	}
	while ((*argv)[i])
		i++;
	new = malloc((i + 2) * sizeof(char *));
	if (!new)
		return ;
	i = -1;
	while ((*argv)[++i])
		new[i] = (*argv)[i];
	new[i] = ft_strdup(value);
	new[i + 1] = NULL;
	free(*argv);
	*argv = new;
	return ;
}

void	redir_add(t_redir **list, t_token_type type, char *target)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->type = type;
	new->target = ft_strdup(target);
	new->next = NULL;
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	cmd_add_back(t_cmd **list, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
