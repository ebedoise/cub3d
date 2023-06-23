/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: embedois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:31:46 by embedois          #+#    #+#             */
/*   Updated: 2023/02/08 15:25:03 by embedois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
char	*read_it(char *save, int fd);
char	*line_it(char *save);
char	*save_it(char *save, int i, int j);

char	*ft_strjoin(char *s1, char *s2, int i);
char	*ft_strchr(const char *s, int c);

int		ft_strlen(char *s);

void	ft_bzero(void *s, size_t n);

#endif
