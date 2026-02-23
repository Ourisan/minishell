/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <ajuvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:09:33 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/14 14:36:39 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isintrim(char c, const char *set)
{
	int	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (c == set[j])
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*trimmed;

	if (*set == '\0')
		return (ft_strdup((char *)s1));
	i = 0;
	len = ft_strlen((char *)s1);
	while (s1[i] != '\0' && ft_isintrim(s1[i], set))
		i++;
	len--;
	while (len > 0 && ft_isintrim(s1[len], set))
		len--;
	trimmed = ft_substr(s1, i, len - i + 1);
	return (trimmed);
}
