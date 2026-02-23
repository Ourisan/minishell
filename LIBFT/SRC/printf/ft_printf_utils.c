/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:21:18 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/25 17:56:40 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_caps_putnbr(long int n, int base)
{
	int		res;
	char	*str_base_caps;

	res = 0;
	str_base_caps = "0123456789ABCDEF";
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n == 0)
		return (ft_putchar('0'));
	if (n < 0)
	{
		res += ft_putchar('-');
		n = n * -1;
	}
	if (n >= 0 && n < base)
		res += ft_putchar(str_base_caps[n]);
	else
	{
		res += ft_caps_putnbr(n / base, base);
		res += ft_caps_putnbr(n % base, base);
	}
	return (res);
}

int	ft_putnbr(long int n, int base)
{
	int		res;
	char	*str_base;

	str_base = "0123456789abcdef";
	res = 0;
	if (n < 0)
	{
		res += ft_putchar('-');
		n = n * -1;
	}
	if (n >= 0 && n < base)
		res += ft_putchar(str_base[n]);
	else
	{
		res += ft_putnbr(n / base, base);
		res += ft_putnbr(n % base, base);
	}
	return (res);
}

int	ft_putpointer(unsigned long int n, int base)
{
	int		res;
	char	*str_base;

	str_base = "0123456789abcdef";
	res = 0;
	if (n < (unsigned long int)base)
		res += ft_putchar(str_base[n]);
	else
	{
		res += ft_putpointer(n / base, base);
		res += ft_putpointer(n % base, base);
	}
	return (res);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}
