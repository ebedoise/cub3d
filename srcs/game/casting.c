#include "cub.h"

void	__erase_old_frame(t_game *g)
{
	int	j;
	int	h;

	j = 0;
	while (j < 1280)
	{
		h = 0;
		while (h < 720)
		{
			my_mlx_pixel_put(&g->img, j, h, 0x00000000);
			h++;
		}
		j++;
	}
}

void	__init_calc(t_game *g, t_casting *c, int x)
{
	c->camera_x = 2 * x / (double)windowW - 1;
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
			c->side = 0;
		}
		else
		{
			c->side_dist_y += c->delta_dist_y;
			c->map_y += c->step_y;
			c->side = 1;
		}
		if (g->map[c->map_x][c->map_y]  == '1')
			c->hit = 1;
	}
}

void	__prep_print_view(t_game *g, t_casting *c)
{
	if (c->side == 0)
		c->perp_wall_dist = (c->map_x - g->pos_x + (1 - c->step_x) / 2) / c->ray_dir_x;
	else
		c->perp_wall_dist = (c->map_y - g->pos_y + (1 - c->step_y) / 2) / c->ray_dir_y;
//	if (c->side == 0)
//		c->perp_wall_dist = (c->side_dist_x - c->delta_dist_x);
//	else
//		c->perp_wall_dist = (c->side_dist_y - c->delta_dist_y);
	c->line_height = (int)(windowH / c->perp_wall_dist);
	c->draw_start = (-1 * c->line_height) / 2 + windowH / 2;
	if (c->draw_start < 0)
		c->draw_start = 0;
	c->draw_end = c->line_height / 2 + windowH / 2;
	if (c->draw_end >= windowH)
		c->draw_end = windowH - 1;
}

void	__print_view(t_game *g, t_casting *c, int x)
{
	int	i;

	i = 0;
	while (i < c->draw_start)
	{
		my_mlx_pixel_put(&g->img, x, i, 0x00FF00FF);
		i++;
	}
	i = 0;
	if (c->side)
		c->color = 0x00FF0000;
	else
		c->color = 0x000000FF;
	while (c->draw_start + i < c->draw_end)
	{
		my_mlx_pixel_put(&g->img, x, c->draw_start + i, c->color);
		i++;
	}
	while (c->draw_end < windowH)
	{
		my_mlx_pixel_put(&g->img, x, c->draw_end, 0x00FFFF);
		c->draw_end++;
	}
}

void	__print_frame(t_game *g)
{
	int		x;
	t_casting	c;

	x = 0;
	__erase_old_frame(g);
	while (x < windowW)
	{
		__init_calc(g, &c, x);
		__dist_inter(g, &c);
		__dda(g, &c);
		__prep_print_view(g, &c);
		__print_view(g, &c, x);
		x++;
	}
//	__minimap(g);
//	__minimap_v2(g);
	mlx_put_image_to_window(g->vars.mlx, g->vars.win, g->img.img, 0, 0);
}
