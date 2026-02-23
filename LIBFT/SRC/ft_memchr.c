/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:11:52 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/14 17:43:29 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t size)
{
	size_t				i;
	unsigned char		*str;

	i = 0;
	str = (unsigned char *)s;
	if (size == 0)
		return (NULL);
	while (i + 1 < size && str[i] != (unsigned char)c)
		i++;
	if (str[i] == (unsigned char)c)
		return ((void *)&str[i]);
	return (NULL);
}
