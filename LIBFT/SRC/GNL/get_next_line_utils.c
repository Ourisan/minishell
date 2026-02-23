/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <ajuvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:11:19 by ajuvin            #+#    #+#             */
/*   Updated: 2025/12/03 02:32:47 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen2(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup2(char *src)
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen2(src);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	size = ft_strlen2((char *)s1) + ft_strlen2((char *)s2) + 1;
	str = malloc(size * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr2(const char *str, int c)
{
	int				i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)str;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[i]);
	return (0);
}

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	size;
	unsigned int	i;

	i = 0;
	if (s == 0)
		return (NULL);
	if (start >= ft_strlen2((char *)s))
		return (ft_strdup2(""));
	if (ft_strlen2((char *)s) < len + start)
		size = (unsigned int)ft_strlen2((char *)s) - start;
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
