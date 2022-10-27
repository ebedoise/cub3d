#include "cub.h"

void	__print_frame(t_game *g)
{
	int	i;
	int	x;
	int	mapX;
	int	mapY;
	int	stepX;
	int	stepY;
	int	hit;
	int	side;
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	int	color;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;

	////////erase old frame ??
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
	x = 0;
	while (x < windowW)
	{
		cameraX = 2 * x / (double)windowW - 1;
		rayDirX = g->dir_x - g->plane_x * cameraX;
		rayDirY = g->dir_y - g->plane_y * cameraX;
		mapX = (int)g->pos_x;
		mapY = (int)g->pos_y;
		deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		hit = 0;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (g->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - g->pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (g->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - g->pos_y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (g->map[mapX][mapY]  == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		lineHeight = (int)(windowH / perpWallDist);
		drawStart = (-1 * lineHeight) / 2 + windowH / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + windowH / 2;
		if (drawEnd >= windowH)
			drawEnd = windowH - 1;
		i = 0;
		while (i < drawStart)
		{
			my_mlx_pixel_put(&g->img, x, i, 0x00FF00FF);
			i++;
		}
		i = 0;
		if (side)
			color = 0x00FF0000;
		else
			color = 0x000000FF;
		while (drawStart + i < drawEnd)
		{
			my_mlx_pixel_put(&g->img, x, drawStart + i, color);
			i++;
		}
		while (drawEnd < windowH)
		{
			my_mlx_pixel_put(&g->img, x, drawEnd, 0x00FFFF);
			drawEnd++;
		}
		x++;
	}
	__minimap(g);
	__minimap_v2(g);
	mlx_put_image_to_window(g->vars.mlx, g->vars.win, g->img.img, 0, 0);
}
