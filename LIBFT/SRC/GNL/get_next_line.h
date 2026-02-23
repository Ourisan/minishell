/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <ajuvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:25:47 by ajuvin            #+#    #+#             */
/*   Updated: 2025/11/17 19:02:54 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

size_t	ft_strlen2(const char *str);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_strdup2(char *src);
char	*ft_strchr2(const char *str, int c);
char	*ft_substr2(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);

#endif
