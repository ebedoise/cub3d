#include "cub.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	__destroy(t_game *g)
{
	mlx_destroy_window(g->vars.mlx, g->vars.win);
	mlx_destroy_display(g->vars.mlx);
	free(g->vars.mlx);
	exit(0);
}

int	__close_window(t_game *g)
{
	__destroy(g);
	exit(0);
	return (0);
}

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
		rayDirX = g->dir_x + g->plane_x * cameraX;
		rayDirY = g->dir_y + g->plane_y * cameraX;
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
	mlx_put_image_to_window(g->vars.mlx, g->vars.win, g->img.img, 0, 0);
}

int	__key_hook(int keycode, t_game *g)
{
	double	save;
	double	oldDirX;
	double	oldPlaneX;

	if (keycode == 119)//W
	{
		save = g->pos_x + g->dir_x * 0.5;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x += g->dir_x * 0.5;
		save = g->pos_y + g->dir_y * 0.5;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y += g->dir_y * 0.5;
	}
	if (keycode == 97)//A
	{
		save = g->pos_x - g->dir_x * 0.5;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x -= g->dir_x * 0.5;
		save = g->pos_y + g->dir_y * 0.5;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y += g->dir_y * 0.5;
	}
	if (keycode == 115)//S
	{
		save = g->pos_x - g->dir_x * 0.5;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x -= g->dir_x * 0.5;
		save = g->pos_y - g->dir_y * 0.5;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y -= g->dir_y * 0.5;
	}
	if (keycode == 100)//D
	{
		save = g->pos_x + g->dir_x * 0.5;
		if (g->map[(int)save][(int)g->pos_y] != '1')
			g->pos_x += g->dir_x * 0.5;
		save = g->pos_y - g->dir_y * 0.5;
		if (g->map[(int)g->pos_x][(int)save] != '1')
			g->pos_y -= g->dir_y * 0.5;
	}
	if (keycode == 65361)//<-
	{
		oldDirX = g->dir_x;
		g->dir_x = g->dir_x * cos(-0.1) - g->dir_y * sin(-0.1);
		g->dir_y = oldDirX * sin(-0.1) + g->dir_y * cos(-0.1);
		oldPlaneX = g->plane_x;
		g->plane_x = g->plane_x * cos(-0.1) - g->plane_y * sin(-0.1);
		g->plane_y = oldPlaneX * sin(-0.1) + g->plane_y * cos(-0.1);
	}
	if (keycode == 65363)//->
	{
		oldDirX = g->dir_x;
		g->dir_x = g->dir_x * cos(0.1) - g->dir_y * sin(0.1);
		g->dir_y = oldDirX * sin(0.1) + g->dir_y * cos(0.1);
		oldPlaneX = g->plane_x;
		g->plane_x = g->plane_x * cos(0.1) - g->plane_y * sin(0.1);
		g->plane_y = oldPlaneX * sin(0.1) + g->plane_y * cos(0.1);
	}
	if (keycode == 65307)
		__destroy(g);
	__print_frame(g);
	return (0);
}

int	__play(t_game g)
{
	g.vars.mlx = mlx_init();
	if (!g.vars.mlx)
		return (1);
	g.vars.win = mlx_new_window(g.vars.mlx, windowW, windowH, "cub3D");
	g.img.img = mlx_new_image(g.vars.mlx, 1280, 720);
	g.img.addr = mlx_get_data_addr(g.img.img, &g.img.bits_per_pixel\
		, &g.img.line_length, &g.img.endian);
	__print_frame(&g);
	mlx_hook(g.vars.win, 2, 1L << 0, __key_hook, &g);
	mlx_hook(g.vars.win, 17, 0, __close_window, &g);
	mlx_loop(g.vars.mlx);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_game	g;

	if (__input(ac, av, env))
		return (1);
	else
	{
		if (__file_checks(av[1], &g))
			return (1);
		g.time = 0;
		g.old_time = 0;
/*		printf("           -- DATA --\n");
		printf("---------------------------------\n");
		printf("f.r = %d | f.g = %d | f.b = %d\n", g.f.r, g.f.g, g.f.b);
		printf("c.r = %d | c.g = %d | c.b = %d\n", g.c.r, g.c.g, g.c.b);
		printf("no = %s\n", g.no);
		printf("so = %s\n", g.so);
		printf("we = %s\n", g.we);
		printf("ea = %s\n", g.ea);
		printf("start_x = %f\n", g.pos_x);
		printf("start_y = %f\n", g.pos_y);
		printf("dir_x = %f\n", g.dir_x);
		printf("dir_y = %f\n", g.dir_y);
		printf("---------------------------------\n");
		printf("           -- MAP --\n");
		printf("---------------------------------\n");
		for (int i = 0; g.map[i]; i++)
			printf("%s\n", g.map[i]);
*/		if (__play(g))
			return (1);
		__free_split(g.map);
		free(g.no);
		free(g.so);
		free(g.we);
		free(g.ea);
	}
	return (0);
}
