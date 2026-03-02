/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:57:46 by lde-plac          #+#    #+#             */
/*   Updated: 2026/03/02 17:08:03 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_identifier(const char *s)
{
    int i;

    i = 0;
    if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
        return (0);
    while (s[++i] && s[i] != '=' && !(s[i] == '+' && s[i+1] == '='))
        if (!ft_isalnum(s[i]) && s[i] != '_')
            return (0);
    return (1);
}
