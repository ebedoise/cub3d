#include "cub_bonus.h"

void	__init_calc(t_game *g, t_casting *c, int x)
{
	c->camera_x = 2 * x / (double)W_W - 1;
	c->ray_dir_x = g->dir_x - g->plane_x * c->camera_x;
	c->ray_dir_y = g->dir_y - g->plane_y * c->camera_x;
	c->map_x = (int)g->pos_x;
	c->map_y = (int)g->pos_y;
	c->delta_dist_x = sqrt(1 + (c->ray_dir_y * c->ray_dir_y) \
		/ (c->ray_dir_x * c->ray_dir_x));
	c->delta_dist_y = sqrt(1 + (c->ray_dir_x * c->ray_dir_x) \
		/ (c->ray_dir_y * c->ray_dir_y));
	c->hit = 0;
}

void	__dist_inter(t_game *g, t_casting *c)
{
	if (c->ray_dir_x < 0)
	{
		c->step_x = -1;
		c->side_dist_x = (g->pos_x - c->map_x) * c->delta_dist_x;
	}
	else
	{
		c->step_x = 1;
		c->side_dist_x = (c->map_x + 1.0 - g->pos_x) * c->delta_dist_x;
	}
	if (c->ray_dir_y < 0)
	{
		c->step_y = -1;
		c->side_dist_y = (g->pos_y - c->map_y) * c->delta_dist_y;
	}
	else
	{
		c->step_y = 1;
		c->side_dist_y = (c->map_y + 1.0 - g->pos_y) * c->delta_dist_y;
	}
}

void	__dda(t_game *g, t_casting *c)
{
	while (c->hit == 0)
	{
		if (c->side_dist_x < c->side_dist_y)
		{
			c->side_dist_x += c->delta_dist_x;
			c->map_x += c->step_x;
			if (c->step_x == -1)
				c->side = 0;
			else
				c->side = 1;
		}
		else
		{
			c->side_dist_y += c->delta_dist_y;
			c->map_y += c->step_y;
			if (c->step_y == -1)
				c->side = 2;
			else
				c->side = 3;
		}
		if (g->map[c->map_x][c->map_y] == '1'
			|| (g->doors == 1 && g->map[c->map_x][c->map_y] == 'D'))
			c->hit = 1;
	}
}

void	__prep_print_view(t_game *g, t_casting *c)
{
	if (c->side == 0 || c->side == 1)
		c->perp_wall_dist = (c->map_x - g->pos_x + (1 - c->step_x) \
			/ 2) / c->ray_dir_x;
	else
		c->perp_wall_dist = (c->map_y - g->pos_y + (1 - c->step_y) \
			/ 2) / c->ray_dir_y;
	c->line_height = (int)(W_H / c->perp_wall_dist);
	c->draw_start = (-1 * c->line_height) / 2 + W_H / 2;
	if (c->draw_start < 0)
		c->draw_start = 0;
	c->draw_end = c->line_height / 2 + W_H / 2;
	if (c->draw_end >= W_H)
		c->draw_end = W_H - 1;
}

void	__print_frame(t_game *g)
{
	t_casting	c;
	int			x;

	x = 0;
	while (x < W_W)
	{
		__init_calc(g, &c, x);
		__dist_inter(g, &c);
		__dda(g, &c);
		__prep_print_view(g, &c);
		__print_view(g, &c, x, 0);
		x++;
	}
	__minimap(g);
	mlx_put_image_to_window(g->vars.mlx, g->vars.win, g->img.img, 0, 0);
	__print_vitals(g);
	__print_keys(g);
}
