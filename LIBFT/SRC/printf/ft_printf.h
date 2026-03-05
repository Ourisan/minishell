/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:48:09 by ajuvin            #+#    #+#             */
/*   Updated: 2026/03/05 15:55:20 by lde-plac         ###   ########.fr       */
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

int	ft_putchar(int fd, char c);
int	ft_putstr(int fd, char *s);
int	ft_putnbr(int fd, long int n, int base);
int	ft_caps_putnbr(int fd, long int n, int base);
int	ft_putpointer(int fd, unsigned long int n, int base);
int	ft_printf(const char *str, ...);
int	ft_printf_fd(int fd, const char *str, ...);

#endif
