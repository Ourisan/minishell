/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:18:24 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/14 17:42:36 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!src && !dest)
		return (0);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	i = -1;
	if (dest > src)
	{
		while (size > 0)
		{
			d[size - 1] = s[size - 1];
			size--;
		}
	}
	else
	{
		while (++i < size)
			d[i] = s[i];
	}
	return (dest);
}
