/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: embedois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:23:56 by embedois          #+#    #+#             */
/*   Updated: 2022/03/02 17:32:54 by embedois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_it(char *save, int i, int j)
{
	char	*str;

	if (save[0] == 0)
	{
		free(save);
		return (NULL);
	}
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!str)
		return (NULL);
	while (save[i + j])
	{
		str[j] = save[i + j];
		j++;
	}
	str[j] = '\0';
	free(save);
	return (str);
}

char	*line_it(char *save)
{
	char	*str;
	int		i;

	i = 0;
	if (save[0] == 0)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		str = malloc(sizeof(char) * (i + 2));
	else
		str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*read_it(char *save, int fd)
{
	char	*buf;
	int		c;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	ft_bzero(buf, BUFFER_SIZE + 1);
	c = 1;
	while (!ft_strchr(buf, '\n') && c != 0)
	{
		c = read(fd, buf, BUFFER_SIZE);
		if (c == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[c] = 0;
		save = ft_strjoin(save, buf, 0);
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[1025];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = read_it(save[fd], fd);
	if (!save[fd])
	{
		free(save[fd]);
		return (NULL);
	}
	line = line_it(save[fd]);
	save[fd] = save_it(save[fd], 0, 0);
	return (line);
}
