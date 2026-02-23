/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <ajuvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:48:09 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/25 17:21:36 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>

int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(long int n, int base);
int	ft_caps_putnbr(long int n, int base);
int	ft_printf(const char *str, ...);
int	ft_putpointer(unsigned long int n, int base);

#endif
