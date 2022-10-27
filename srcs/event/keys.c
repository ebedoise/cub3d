#include "cub.h"

void	__front_back(int keycode, t_game *g)
{
	double	save;

	if (keycode == 119) //W
	{
		save = g->pos_x + g->dir_x * 0.17;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x += g->dir_x * 0.17;
		save = g->pos_y + g->dir_y * 0.17;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y += g->dir_y * 0.17;
	}
	else if (keycode == 115) //S
	{
		save = g->pos_x - g->dir_x * 0.17;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x -= g->dir_x * 0.17;
		save = g->pos_y - g->dir_y * 0.17;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y -= g->dir_y * 0.17;
	}
}

void	__right_left(int keycode, t_game *g)
{
	double	save;

	if (keycode == 100) //D
	{
		save = g->pos_x - g->plane_x * 0.17;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x -= g->plane_x * 0.17;
		save = g->pos_y - g->plane_y * 0.17;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y -= g->plane_y * 0.17;
	}
	else if (keycode == 97) //A
	{
		save = g->pos_x + g->plane_x * 0.17;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x += g->plane_x * 0.17;
		save = g->pos_y + g->plane_y * 0.17;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y += g->plane_y * 0.17;
	}
}

void	__arrows(int keycode, t_game *g)
{
	double	old_dir;
	double	old_plane;

	if (keycode == 65363) //->
	{
		old_dir = g->dir_x;
		g->dir_x = g->dir_x * cos(-0.12) - g->dir_y * sin(-0.12);
		g->dir_y = old_dir * sin(-0.12) + g->dir_y * cos(-0.12);
		old_plane = g->plane_x;
		g->plane_x = g->plane_x * cos(-0.12) - g->plane_y * sin(-0.12);
		g->plane_y = old_plane * sin(-0.12) + g->plane_y * cos(-0.12);
	}
	else if (keycode == 65361) //<-
	{
		old_dir = g->dir_x;
		g->dir_x = g->dir_x * cos(0.12) - g->dir_y * sin(0.12);
		g->dir_y = old_dir * sin(0.12) + g->dir_y * cos(0.12);
		old_plane = g->plane_x;
		g->plane_x = g->plane_x * cos(0.12) - g->plane_y * sin(0.12);
		g->plane_y = old_plane * sin(0.12) + g->plane_y * cos(0.12);
	}
}

int	__key_hook(int keycode, t_game *g)
{
	g->move_speed = 0.17;
	g->rot_speed = 0.12;
	if (keycode == 119 || keycode == 115)
		__front_back(keycode, g);
	else if (keycode == 100 || keycode == 97)
		__right_left(keycode, g);
	else if (keycode == 65363 || keycode == 65361)
		__arrows(keycode, g);
	else if (keycode == 65307)
		__destroy(g);
	__print_frame(g);
	return (0);
}
