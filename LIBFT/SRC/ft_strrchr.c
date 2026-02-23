/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:49:24 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/14 17:21:04 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen((char *)str);
	while (i > 0 && str[i] != (unsigned char)c)
		i--;
	if (str[i] == (unsigned char)c)
		return ((char *)&str[i]);
	return (0);
}
