/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: embedois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:25:59 by embedois          #+#    #+#             */
/*   Updated: 2023/02/08 15:26:01 by embedois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	__left_arrow(t_game *g, double old_dir, double old_plane)
{
	old_dir = g->dir_x;
	g->dir_x = g->dir_x * cos(g->rot_speed) \
		- g->dir_y * sin(g->rot_speed);
	g->dir_y = old_dir * sin(g->rot_speed) \
		+ g->dir_y * cos(g->rot_speed);
	old_plane = g->plane_x;
	g->plane_x = g->plane_x * cos(g->rot_speed) \
		- g->plane_y * sin(g->rot_speed);
	g->plane_y = old_plane * sin(g->rot_speed) \
		+ g->plane_y * cos(g->rot_speed);
}

void	__right_arrow(t_game *g, double old_dir, double old_plane)
{
	old_dir = g->dir_x;
	g->dir_x = g->dir_x * cos(-(g->rot_speed)) \
		- g->dir_y * sin(-(g->rot_speed));
	g->dir_y = old_dir * sin(-(g->rot_speed)) \
		+ g->dir_y * cos(-(g->rot_speed));
	old_plane = g->plane_x;
	g->plane_x = g->plane_x * cos(-(g->rot_speed)) \
		- g->plane_y * sin(-(g->rot_speed));
	g->plane_y = old_plane * sin(-(g->rot_speed)) \
		+ g->plane_y * cos(-(g->rot_speed));
}

void	__arrows(t_game *g, int i)
{
	double	old_dir;
	double	old_plane;

	old_dir = 0.0;
	old_plane = 0.0;
	if (!i)
	{
		g->rot_speed = 0.01;
		__right_arrow(g, old_dir, old_plane);
		g->rot_speed = 0.02;
		__left_arrow(g, old_dir, old_plane);
	}
	else
	{
		if (g->w || g->a || g->s || g->d)
			g->rot_speed = 0.04;
		else
			g->rot_speed = 0.07;
		if (g->right)
			__right_arrow(g, old_dir, old_plane);
		if (g->left)
			__left_arrow(g, old_dir, old_plane);
	}
}
