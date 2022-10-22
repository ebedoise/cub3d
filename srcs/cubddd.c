#include "cub.h"
//////////////////////////////////////////////////////////////////////
typedef struct	s_d {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_d;

void	my_mlx_pixel_put(t_d *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	__print_vertical(t_game g, int x, int start, int end, int color)
{
	t_d	img;

	(void)end;
	img.img = mlx_new_image(g.vars.mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel\
		, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, start, x, color);
	mlx_put_image_to_window(g.vars.mlx, g.vars.win, img.img, 0, 0);
	return (0);
}
////////////////////////////////////////////////////////////////////
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

int	__key_hook(int keycode, t_game *g)
{
	if (keycode == 119)
		g->pos_y -= 1;
	if (keycode == 97)
		g->pos_x -= 1;
	if (keycode == 115)
		g->pos_y += 1;
	if (keycode == 100)
		g->pos_x += 1;
	if (keycode == 65307)
		__destroy(g);
	return (0);
}

int	__play(t_game g)
{
	g.vars.mlx = mlx_init();
	if (!g.vars.mlx)
		return (1);
	g.vars.win = mlx_new_window(g.vars.mlx, windowW, windowH, "cub3D");

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
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;

	x = 0;
	while (x < windowW)
	{
		cameraX = 2 * x / (double)windowW - 1;
		rayDirX = g.dir_x + g.plane_x * cameraX;
		rayDirY = g.dir_y + g.plane_y * cameraX;
		mapX = (int)g.pos_x;
		mapY = (int)g.pos_y;
		deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		hit = 0;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (g.pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - g.pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (g.pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - g.pos_y) * deltaDistY;
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
			if (g.map[mapX][mapY]  == '1')
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
		__print_vertical(g, x, drawStart, drawEnd, 0x00FFFFFF);
		x++;
	}

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
		g.plane_x = 0;
		g.plane_y = 0.66;
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
