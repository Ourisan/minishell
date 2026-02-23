/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:20:18 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/14 01:37:07 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	size_t				i;
	const unsigned char	*s1_ptr;
	const unsigned char	*s2_ptr;

	if (size == 0)
		return (0);
	i = 0;
	s1_ptr = (const unsigned char *)s1;
	s2_ptr = (const unsigned char *)s2;
	while (s1_ptr[i] == s2_ptr[i] && i < size - 1)
		i++;
	if (s1_ptr[i] > s2_ptr[i])
		return (1);
	else if (s1_ptr[i] < s2_ptr[i])
		return (-1);
	return (0);
}
