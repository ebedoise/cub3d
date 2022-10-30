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
			my_mlx_pixel_put(&img, j + x + 8, i + y + 8, color);
			y++;
		}
		x++;
	}
}

void	__print_block_v2(t_img img, int i, int j, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < 8)
	{
		y = 0;
		while (y < 8)
		{
			my_mlx_pixel_put(&img, j + x + W_W / 2, i + y, color);
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
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == '1')
				__print_block(g->img, i * 8, j * 8, 0x00FFFFFF);
			else if (g->map[i][j] != ' ')
				__print_block(g->img, i * 8, j * 8, 0x00000000);
			j++;
		}
		i++;
	}
	__print_block(g->img, g->pos_x * 8, g->pos_y * 8, 0x00FF00FF);
}

void	__minimap_v2(t_game *g, int i, int j)
{
	int	x;
	int	y;

	x = g->pos_x - 8;
	while (i < 17)
	{
		j = 0;
		y = g->pos_y - 8;
		while (j < 17)
		{
			if (i == 8 && j == 8)
				__print_block_v2(g->img, i * 8, j * 8, 0x00FF00FF);
			else if (x >= 0 && y >= 0 && x < g->map_max
				&& y < __strlen(g->map[x])
				&& g->map[x][y] && g->map[x][y] == '1')
				__print_block_v2(g->img, i * 8, j * 8, 0x00FFFFFF);
			else
				__print_block_v2(g->img, i * 8, j * 8, 0x00000000);
			j++;
			y++;
		}
		i++;
		x++;
	}
}
