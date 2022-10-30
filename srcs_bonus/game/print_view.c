#include "cub_bonus.h"

void	__print_ceiling(t_game *g, t_casting *c, int x, int i)
{
	c->color = ((g->c.r & 0xff) << 16) + ((g->c.g & 0xff) << 8) \
		+ (g->c.b & 0xff);
	while (i < c->draw_start)
	{
		my_mlx_pixel_put(&g->img, x, i, c->color);
		i++;
	}
}

void	__print_floor(t_game *g, t_casting *c, int x)
{
	c->color = ((g->f.r & 0xff) << 16) + ((g->f.g & 0xff) << 8) \
		+ (g->f.b & 0xff);
	while (c->draw_end < W_H)
	{
		my_mlx_pixel_put(&g->img, x, c->draw_end, c->color);
		c->draw_end++;
	}
}

void	__print_view(t_game *g, t_casting *c, int x, int i)
{
	__print_ceiling(g, c, x, i);
	i = 0;
	if (c->side == 0 || c->side == 1)
	{
		c->color = 0x000000FF;
		if (c->side == 1)
			c->color = c->color / 2;
	}
	else
	{
		c->color = 0x00FF0000;
		if (c->side == 3)
			c->color = c->color / 3;
	}
	while (c->draw_start + i < c->draw_end)
	{
		my_mlx_pixel_put(&g->img, x, c->draw_start + i, c->color);
		i++;
	}
	__print_floor(g, c, x);
}
