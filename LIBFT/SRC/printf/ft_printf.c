/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 12:39:24 by ajuvin            #+#    #+#             */
/*   Updated: 2026/01/12 16:13:47 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	isconv(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'u' || c == 'x'
		|| c == 'X' || c == '%' || c == 'i')
		return (1);
	return (0);
}

int	ft_args2(va_list tab, char c)
{
	int	res;

	res = 0;
	if (c == 'd' || c == 'i')
		res += ft_putnbr(va_arg(tab, int), 10);
	if (c == 'u')
		res += ft_putnbr(va_arg(tab, unsigned int), 10);
	if (c == 'x')
		res += ft_putnbr(va_arg(tab, unsigned int), 16);
	if (c == 'X')
		res += ft_caps_putnbr(va_arg(tab, unsigned int), 16);
	if (c == '%')
		res += ft_putchar('%');
	return (res);
}

int	ft_args1(va_list tab, char c)
{
	int					res;
	unsigned long int	n;

	res = 0;
	if (c == 'c')
		res += ft_putchar(va_arg(tab, int));
	else if (c == 's')
		res += ft_putstr(va_arg(tab, char *));
	else if (c == 'p')
	{
		n = (unsigned long int)va_arg(tab, void *);
		if (n == 0)
			return (ft_putstr("(nil)"));
		res += ft_putstr("0x");
		res += ft_putpointer(n, 16);
	}
	else
		return (ft_args2(tab, c));
	return (res);
}

int	ft_printf(const char *str, ...)
{
	va_list	tab;
	int		i;
	int		res;

	va_start(tab, str);
	if (!str)
		return (-1);
	i = 0;
	res = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0' && isconv(str[i + 1]) == 1)
		{
			i++;
			res += ft_args1(tab, str[i]);
			i++;
			if (str[i] == '\0')
				return (res);
		}
		else
			res += ft_putchar(str[i++]);
	}
	va_end(tab);
	return (res);
}
