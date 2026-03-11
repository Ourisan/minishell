/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ourisan <ourisan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:34:36 by ajuvin            #+#    #+#             */
/*   Updated: 2026/03/11 18:36:26 by ourisan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;
	size_t	pos;

	if (*little == '\0')
		return ((char *)big);
	i = SIZE_MAX;
	j = 0;
	while (big[++i] != '\0')
	{
		if (big[i] == little[j])
		{
			if (j == 0)
				pos = i;
			j++;
		}
		else if (little[j] != '\0' && j != 0)
		{
			j = 0;
			i = pos;
		}
	}
	if (j == ft_strlen(little))
		return ((char *)&big[pos]);
	return (0);
}
