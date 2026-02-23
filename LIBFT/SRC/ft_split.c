/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <ajuvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:55:08 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/20 16:18:21 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **strs, int size)
{
	while (--size >= 0)
		free(strs[size]);
	free(strs);
	return (NULL);
}

int	ft_countword(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i - 1] != c)
			count++;
	}
	return (count);
}

static char	**ft_write(char const *s, char **strs, char c)
{
	int	i;
	int	start;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (!(s[i] != '\0' && s[i - 1] == c) && i > start)
		{
			strs[count] = ft_substr(s, start, (size_t)(i - start));
			if (!strs[count])
				return (ft_free(strs, count));
		}
		if (s[i - 1] != c)
			count++;
	}
	strs[count] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	strs = malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	if (!ft_write(s, strs, c))
		return (NULL);
	return (strs);
}
