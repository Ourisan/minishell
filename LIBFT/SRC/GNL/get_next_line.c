/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuvin <ajuvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:25:42 by ajuvin            #+#    #+#             */
/*   Updated: 2025/12/20 18:11:59 by ajuvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line(int fd, char *new_l, char *buffer)
{
	ssize_t	read_r;
	char	*tmp;

	read_r = 1;
	while (read_r > 0)
	{
		read_r = read(fd, buffer, BUFFER_SIZE);
		if (read_r == -1)
			return (free(new_l), NULL);
		if (read_r == 0)
			break ;
		if (!new_l)
			new_l = ft_strdup2("");
		buffer[read_r] = '\0';
		tmp = new_l;
		new_l = ft_strjoin2(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr2(buffer, '\n') != 0)
			break ;
	}
	return (new_l);
}

static char	*set_new_l(char *line)
{
	ssize_t		i;
	char		*new_l;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[0] == '\0')
		return (NULL);
	new_l = ft_substr2(line, i + 1, ft_strlen2(line) - i - 1);
	if (new_l[0] == '\0')
	{
		free(new_l);
		new_l = NULL;
	}
	if (line[i] != '\0')
		line[i + 1] = '\0';
	return (new_l);
}

char	*get_next_line(int fd)
{
	static char	*new_l;
	char		*buffer;
	char		*line;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(new_l), free(buffer), new_l = NULL, buffer = NULL, NULL);
	if (!buffer)
		return (NULL);
	line = fill_line(fd, new_l, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	new_l = set_new_l(line);
	return (line);
}
