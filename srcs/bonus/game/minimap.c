/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: embedois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:29:16 by embedois          #+#    #+#             */
/*   Updated: 2023/02/08 15:29:17 by embedois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	__print_block(t_img img, int i, int j, int color)
{
	int	x;
	int	y;

	x = -4;
	while (x < 4)
	{
		y = -4;
		while (y < 4)
		{
			my_mlx_pixel_put(&img, j + x + 9, i + y + 9, color);
			y++;
		}
		x++;
	}
}

void	__print_player(t_img img, int i, int j, int color)
{
	int	x;
	int	y;

	x = -2;
	while (x < 2)
	{
		y = -2;
		while (y < 2)
		{
			my_mlx_pixel_put(&img, j + x + 5, i + y + 5, color);
			y++;
		}
		x++;
	}
}

void	__minimap(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	if (g->map_max_x * 8 > W_H / 3 || g->map_max_y * 8 > W_W / 3)
		return ;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == '1')
				__print_block(g->img, i * 8, j * 8, 0x00FFFFFF);
			else if (g->map[i][j] == 'D' && g->doors == 1)
				__print_block(g->img, i * 8, j * 8, 0x00E5E300);
			else if (g->map[i][j] == 'D' && g->doors == -1)
				__print_block(g->img, i * 8, j * 8, 0x00C8C8C8);
			else if (g->map[i][j] != ' ')
				__print_block(g->img, i * 8, j * 8, 0x00000000);
			j++;
		}
		i++;
	}
	__print_player(g->img, g->pos_x * 8, g->pos_y * 8, 0x00FF00FF);
}
