#include "cub_bonus.h"

void	__left_mouse(t_game *g)
{
	double	old_dir;
	double	old_plane;

	old_dir = 0.0;
	old_plane = 0.0;
	if (g->w || g->a || g->s || g->d)
		g->rot_speed = 0.01;
	else
		g->rot_speed = 0.04;
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

void	__right_mouse(t_game *g)
{
	double	old_dir;
	double	old_plane;

	old_dir = 0.0;
	old_plane = 0.0;
	if (g->w || g->a || g->s || g->d)
		g->rot_speed = 0.01;
	else
		g->rot_speed = 0.04;
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

int	__mouse_move(int x, int y, t_game *g)
{
	mlx_mouse_move(g->vars.mlx, g->vars.win, W_W / 2, W_H / 2);
	g->mouse_x = x;
	(void)y;
	return (0);
}
