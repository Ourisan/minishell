/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:53:26 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/13 18:46:32 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!src && !dest)
		return (0);
	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	i = 0;
	while (i < size)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
