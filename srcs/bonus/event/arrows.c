#include "cub_bonus.h"

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
	if (g->w || g->a || g->s || g->d)
		g->rot_speed = 0.04;
	else
		g->rot_speed = 0.07;
	if (!i)
	{
		g->rot_speed = 0.01;
		__right_arrow(g, old_dir, old_plane);
		__left_arrow(g, old_dir, old_plane);
	}
	else
	{
		if (g->right)
			__right_arrow(g, old_dir, old_plane);
		if (g->left)
			__left_arrow(g, old_dir, old_plane);
	}
}
