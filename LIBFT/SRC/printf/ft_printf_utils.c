/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:21:18 by ajuvin            #+#    #+#             */
/*   Updated: 2026/03/05 15:54:34 by lde-plac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_caps_putnbr(int fd, long int n, int base)
{
	int		res;
	char	*str_base_caps;

	res = 0;
	str_base_caps = "0123456789ABCDEF";
	if (n == -2147483648)
		return (ft_putstr(fd, "-2147483648"));
	if (n == 0)
		return (ft_putchar(fd, '0'));
	if (n < 0)
	{
		res += ft_putchar(fd, '-');
		n = n * -1;
	}
	if (n >= 0 && n < base)
		res += ft_putchar(fd, str_base_caps[n]);
	else
	{
		res += ft_caps_putnbr(fd, n / base, base);
		res += ft_caps_putnbr(fd, n % base, base);
	}
	return (res);
}

int	ft_putnbr(int fd, long int n, int base)
{
	int		res;
	char	*str_base;

	str_base = "0123456789abcdef";
	res = 0;
	if (n < 0)
	{
		res += ft_putchar(fd, '-');
		n = n * -1;
	}
	if (n >= 0 && n < base)
		res += ft_putchar(fd, str_base[n]);
	else
	{
		res += ft_putnbr(fd, n / base, base);
		res += ft_putnbr(fd, n % base, base);
	}
	return (res);
}

int	ft_putpointer(int fd, unsigned long int n, int base)
{
	int		res;
	char	*str_base;

	str_base = "0123456789abcdef";
	res = 0;
	if (n < (unsigned long int)base)
		res += ft_putchar(fd, str_base[n]);
	else
	{
		res += ft_putpointer(fd, n / base, base);
		res += ft_putpointer(fd, n % base, base);
	}
	return (res);
}

int	ft_putstr(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr(fd, "(null)"));
	while (str[i] != '\0')
	{
		ft_putchar(fd, str[i]);
		i++;
	}
	return (i);
}
