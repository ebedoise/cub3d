#include "cub.h"

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

void	__print_block(t_d img, int i, int j, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < 16)
	{
		y = 0;
		while (y < 16)
		{
			my_mlx_pixel_put(&img, (j * 16) + x, (i * 16) + y, color);
			y++;
		}
		x++;
	}
}

int	__print_map(t_game *g)
{
	int	i;
	int	j;
	t_d	img;

	i = 0;
	img.img = mlx_new_image(g->vars.mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel\
		, &img.line_length, &img.endian);
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if (g->map[i][j] == '1')
				__print_block(img, i, j, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	__print_block(img, g->start_y, g->start_x, 0x00FF0000);
	mlx_put_image_to_window(g->vars.mlx, g->vars.win, img.img, 0, 0);
	return (0);
}

int	__key_hook(int keycode, t_game *g)
{
	if (keycode == 119)
		g->start_y -= 1;
	if (keycode == 97)
		g->start_x -= 1;
	if (keycode == 115)
		g->start_y += 1;
	if (keycode == 100)
		g->start_x += 1;
	if (keycode == 65307)
		__destroy(g);
	__print_map(g);
	return (0);
}

int	__play(t_game g)
{
	g.vars.mlx = mlx_init();
	if (!g.vars.mlx)
		return (1);
	g.vars.win = mlx_new_window(g.vars.mlx, 1280, 720, "cub3D");
	__print_map(&g);
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
		printf("           -- DATA --\n");
		printf("---------------------------------\n");
		printf("f.r = %d | f.g = %d | f.b = %d\n", g.f.r, g.f.g, g.f.b);
		printf("c.r = %d | c.g = %d | c.b = %d\n", g.c.r, g.c.g, g.c.b);
		printf("no = %s\n", g.no);
		printf("so = %s\n", g.so);
		printf("we = %s\n", g.we);
		printf("ea = %s\n", g.ea);
		printf("start_x = %f\n", g.start_x);
		printf("start_y = %f\n", g.start_y);
		printf("start_rad = %f\n", g.start_rad);
		printf("---------------------------------\n");
		printf("           -- MAP --\n");
		printf("---------------------------------\n");
		for (int i = 0; g.map[i]; i++)
			printf("%s\n", g.map[i]);
		if (__play(g))
			return (1);
		__free_split(g.map);
		free(g.no);
		free(g.so);
		free(g.we);
		free(g.ea);
	}
	return (0);
}
