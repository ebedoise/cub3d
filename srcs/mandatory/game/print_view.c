/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: embedois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:26:25 by embedois          #+#    #+#             */
/*   Updated: 2023/02/08 15:26:27 by embedois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	__print_ceiling_floor(t_game *g, t_casting *c, int x, int i)
{
	if (!i)
	{
		c->color = ((g->c.r & 0xff) << 16) + ((g->c.g & 0xff) << 8) \
			+ (g->c.b & 0xff);
		while (i < c->draw_start)
		{
			my_mlx_pixel_put(&g->img, x, i, c->color);
			i++;
		}
	}
	else
	{
		c->color = ((g->f.r & 0xff) << 16) + ((g->f.g & 0xff) << 8) \
			+ (g->f.b & 0xff);
		while (c->draw_end < W_H)
		{
			my_mlx_pixel_put(&g->img, x, c->draw_end, c->color);
			c->draw_end++;
		}
	}
}

void	__print_wall(t_game *g, t_casting *c, t_coord coord, t_img wall)
{
	g->img.addr[coord.y * g->img.line_length \
		+ coord.x * g->img.bpp / 8] = \
		wall.addr[c->tex_y * wall.line_length + c->tex_x \
		* (wall.bpp / 8)];
	g->img.addr[coord.y * g->img.line_length \
		+ coord.x * g->img.bpp / 8 + 1] = \
		wall.addr[c->tex_y * wall.line_length + c->tex_x \
		* (wall.bpp / 8) + 1];
	g->img.addr[coord.y * g->img.line_length \
		+ coord.x * g->img.bpp / 8 + 2] = \
		wall.addr[c->tex_y * wall.line_length + c->tex_x \
		* (wall.bpp / 8) + 2];
}

void	__size_tex(t_game *g, t_casting *c)
{
	int	n;

	n = 0;
	if (c->side == 0)
		n = g->no_tex.width;
	else if (c->side == 1)
		n = g->so_tex.width;
	else if (c->side == 2)
		n = g->we_tex.width;
	else if (c->side == 3)
		n = g->ea_tex.width;
	c->tex_x = (int)(c->wall_x * (double)n);
	if ((c->side == 0 || c->side == 1) && c->ray_dir_x > 0)
		c->tex_x = n - c->tex_x - 1;
	if ((c->side == 2 || c->side == 3) && c->ray_dir_y < 0)
		c->tex_x = n - c->tex_x - 1;
	c->step = 1.0 *(double) n / c->line_height;
}

void	__print_walls(t_game *g, t_casting *c, t_coord coord)
{
	if (c->side == 0 || c->side == 1)
		c->wall_x = g->pos_y + c->perp_wall_dist * c->ray_dir_y;
	else
		c->wall_x = g->pos_x + c->perp_wall_dist * c->ray_dir_x;
	c->wall_x -= __floor((c->wall_x));
	__size_tex(g, c);
	c->tex_pos = (c->draw_start - W_H / 2 + c->line_height / 2) * c->step;
	while (++(coord.y) < c->draw_end)
	{
		c->tex_y = (int)c->tex_pos;
		c->tex_pos += c->step;
		if (c->side == 0)
			__print_wall(g, c, coord, g->no_tex);
		else if (c->side == 1)
			__print_wall(g, c, coord, g->so_tex);
		else if (c->side == 2)
			__print_wall(g, c, coord, g->we_tex);
		else if (c->side == 3)
			__print_wall(g, c, coord, g->ea_tex);
	}
}

void	__print_view(t_game *g, t_casting *c, int x, int i)
{
	t_coord	coord;

	coord.x = x;
	coord.y = c->draw_start - 1;
	__print_ceiling_floor(g, c, x, i);
	__print_walls(g, c, coord);
	i = 1;
	__print_ceiling_floor(g, c, x, i);
}
