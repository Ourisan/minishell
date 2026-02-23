/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <ajuvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:51:34 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/14 14:21:37 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	size;
	unsigned int	i;

	i = 0;
	if (s == 0)
		return (NULL);
	if (start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	if (ft_strlen((char *)s) < len + start)
		size = (unsigned int)ft_strlen((char *)s) - start;
	else
		size = len;
	str = malloc(size + 1 * sizeof(char));
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
