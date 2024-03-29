/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: embedois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:28:14 by embedois          #+#    #+#             */
/*   Updated: 2023/02/08 15:28:15 by embedois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	__bzero(t_game *g)
{
	g->no = NULL;
	g->so = NULL;
	g->we = NULL;
	g->ea = NULL;
	g->f.r = -1;
	g->f.g = -1;
	g->f.b = -1;
	g->c.r = -1;
	g->c.g = -1;
	g->c.b = -1;
}

int	__empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	__data_handler(char *str, t_game *g)
{
	if (strncmp(str, "NO ", 3) == 0 || strncmp(str, "SO ", 3) == 0
		|| strncmp(str, "WE ", 3) == 0 || strncmp(str, "EA ", 3) == 0)
	{
		if (__cardinals(str, g))
			return (1);
	}
	else if (strncmp(str, "F ", 2) == 0)
	{
		if (__colors(str, g, 'f', 2))
			return (1);
	}
	else if (strncmp(str, "C ", 2) == 0)
	{
		if (__colors(str, g, 'c', 2))
			return (1);
	}
	else
		return (1);
	return (0);
}

int	__uninit(t_game *g)
{
	if (g->no == NULL || g->so == NULL
		|| g->we == NULL || g->ea == NULL
		|| g->f.r == -1 || g->f.g == -1
		|| g->f.b == -1 || g->c.r == -1
		|| g->c.g == -1 || g->c.b == -1)
		return (1);
	return (0);
}

int	__data_checks(char *str, t_game *g)
{
	char	**strs;
	int		i;

	i = 0;
	__bzero(g);
	strs = __split(str, '\n');
	if (!strs)
		return (__puterr("Malloc err"));
	free(str);
	while (strs[i])
	{
		if (__empty_line(strs[i]) && __data_handler(strs[i], g))
		{
			__free_split(strs);
			return (__puterr("Invalide data in the file"));
		}
		i++;
	}
	if (__uninit(g))
	{
		__free_split(strs);
		return (__puterr("Need more data in the file"));
	}
	__free_split(strs);
	return (0);
}
