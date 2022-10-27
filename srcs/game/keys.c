#include "cub.h"

int	__key_hook(int keycode, t_game *g)
{
	double	save;
	double	oldDirX;
	double	oldPlaneX;

	g->move_speed = 0.17;
	g->rot_speed = 0.12;
	if (keycode == 119)//W
	{
		save = g->pos_x + g->dir_x * 0.17;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x += g->dir_x * 0.17;
		save = g->pos_y + g->dir_y * 0.17;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y += g->dir_y * 0.17;
	}
	if (keycode == 100)//D
	{
		save = g->pos_x - g->plane_x * 0.17;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x -= g->plane_x * 0.17;
		save = g->pos_y - g->plane_y * 0.17;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y -= g->plane_y * 0.17;
	}
	if (keycode == 115)//S
	{
		save = g->pos_x - g->dir_x * 0.17;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x -= g->dir_x * 0.17;
		save = g->pos_y - g->dir_y * 0.17;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y -= g->dir_y * 0.17;
	}
	if (keycode == 97)//A
	{
		save = g->pos_x + g->plane_x * 0.17;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x += g->plane_x * 0.17;
		save = g->pos_y + g->plane_y * 0.17;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y += g->plane_y * 0.17;
	}
	if (keycode == 65363)//->
	{
		oldDirX = g->dir_x;
		g->dir_x = g->dir_x * cos(-0.12) - g->dir_y * sin(-0.12);
		g->dir_y = oldDirX * sin(-0.12) + g->dir_y * cos(-0.12);
		oldPlaneX = g->plane_x;
		g->plane_x = g->plane_x * cos(-0.12) - g->plane_y * sin(-0.12);
		g->plane_y = oldPlaneX * sin(-0.12) + g->plane_y * cos(-0.12);
	}
	if (keycode == 65361)//<-
	{
		oldDirX = g->dir_x;
		g->dir_x = g->dir_x * cos(0.12) - g->dir_y * sin(0.12);
		g->dir_y = oldDirX * sin(0.12) + g->dir_y * cos(0.12);
		oldPlaneX = g->plane_x;
		g->plane_x = g->plane_x * cos(0.12) - g->plane_y * sin(0.12);
		g->plane_y = oldPlaneX * sin(0.12) + g->plane_y * cos(0.12);
	}
	if (keycode == 65307)
		__destroy(g);
	__print_frame(g);
	return (0);
}
