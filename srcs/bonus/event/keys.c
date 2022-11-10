#include "cub_bonus.h"

void	__front_back(t_game *g)
{
	double	save;

	if (g->w)
	{
		save = g->pos_x + g->dir_x * g->move_speed;
		if (g->map[(int)save][(int)g->pos_y] != '1' && (g->doors == -1
			|| g->map[(int)save][(int)g->pos_y] != 'D'))
			g->pos_x += g->dir_x * g->move_speed;
		save = g->pos_y + g->dir_y * g->move_speed;
		if (g->map[(int)g->pos_x][(int)save] != '1'&& (g->doors == -1
			|| g->map[(int)g->pos_x][(int)save] != 'D'))
			g->pos_y += g->dir_y * g->move_speed;
	}
	if (g->s)
	{
		save = g->pos_x - g->dir_x * g->move_speed;
		if (g->map[(int)save][(int)g->pos_y] != '1' && (g->doors == -1
			|| g->map[(int)save][(int)g->pos_y] != 'D'))
			g->pos_x -= g->dir_x * g->move_speed;
		save = g->pos_y - g->dir_y * g->move_speed;
		if (g->map[(int)g->pos_x][(int)save] != '1' && (g->doors == -1
			|| g->map[(int)g->pos_x][(int)save] != 'D'))
			g->pos_y -= g->dir_y * g->move_speed;
	}
}

void	__right_left(t_game *g)
{
	double	save;

	if (g->d)
	{
		save = g->pos_x - g->plane_x * g->move_speed;
		if (g->map[(int)save][(int)g->pos_y] != '1' && (g->doors == -1
			|| g->map[(int)save][(int)g->pos_y] != 'D'))
			g->pos_x -= g->plane_x * g->move_speed;
		save = g->pos_y - g->plane_y * g->move_speed;
		if (g->map[(int)g->pos_x][(int)save] != '1' && (g->doors == -1
			|| g->map[(int)g->pos_x][(int)save] != 'D'))
			g->pos_y -= g->plane_y * g->move_speed;
	}
	if (g->a)
	{
		save = g->pos_x + g->plane_x * g->move_speed;
		if (g->map[(int)save][(int)g->pos_y] != '1' && (g->doors == -1
			|| g->map[(int)save][(int)g->pos_y] != 'D'))
			g->pos_x += g->plane_x * g->move_speed;
		save = g->pos_y + g->plane_y * g->move_speed;
		if (g->map[(int)g->pos_x][(int)save] != '1' && (g->doors == -1
			|| g->map[(int)g->pos_x][(int)save] != 'D'))
			g->pos_y += g->plane_y * g->move_speed;
	}
}

int	__loop(t_game *g)
{
	g->move_speed = 0.06;
	if (g->shift)
		g->move_speed = 0.1;
	if (g->w || g->s)
		__front_back(g);
	if (g->a || g->d)
		__right_left(g);
	if (g->right || g->left)
		__arrows(g, 1);
	if (g->mouse_x < (W_W / 2) - 10)
		__left_mouse(g);
	if (g->mouse_x > (W_W / 2) + 10)
		__right_mouse(g);
	__print_frame(g);
	return (0);
}

int	__key_press(int keycode, t_game *g)
{
	if (keycode == 119)
		g->w = 1;
	else if (keycode == 115)
		g->s = 1;
	else if (keycode == 100)
		g->d = 1;
	else if (keycode == 97)
		g->a = 1;
	else if (keycode == 65363)
		g->right = 1;
	else if (keycode == 65361)
		g->left = 1;
	else if (keycode == 65505)
		g->shift = 1;
	else if (keycode == 65307)
		__destroy(g);
	return (0);
}

int	__key_release(int keycode, t_game *g)
{
	if (keycode == 119)
		g->w = 0;
	else if (keycode == 115)
		g->s = 0;
	else if (keycode == 100)
		g->d = 0;
	else if (keycode == 97)
		g->a = 0;
	else if (keycode == 101)
	{
		if (g->map[(int)g->pos_x][(int)g->pos_y] == 'D')
		{
			printf("GAME OVER\nYou got crushed by a door\n");
			__destroy(g);
		}
		g->doors *= -1;
	}
	else if (keycode == 65363)
		g->right = 0;
	else if (keycode == 65361)
		g->left = 0;
	else if (keycode == 65505)
		g->shift = 0;
	return (0);
}
