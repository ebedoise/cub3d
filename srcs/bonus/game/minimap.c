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
	__print_player(g->img, g->pos_x * 8, g->pos_y * 8, 0x00FF00FF);
}
