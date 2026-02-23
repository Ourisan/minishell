/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <ajuvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:11:28 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/17 02:53:57 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	int	size;

	if (n == -2147483648)
		return (11);
	size = 0;
	if (n < 0)
	{
		size++;
		n = -n;
	}
	if (n == 0)
		size = 1;
	while (n >= 1)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static int	fpow(int n, int pow)
{
	if (pow == 0)
		return (1);
	return (n * (fpow(n, pow - 1)));
}

char	*ft_itoa(int n)
{
	char	*res;
	int		s;
	int		i;
	int		t;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s = ft_size(n);
	res = malloc((s + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	if (n < 0)
	{
		res[i++] = '-';
		n = -n;
	}
	t = 0;
	while (i < s)
	{
		res[i] = ((n - t * (fpow(10, s - i))) / (fpow(10, s - i -1))) + '0';
		t = (n / (fpow(10, s - i++ -1)));
	}
	res[i] = '\0';
	return (res);
}
