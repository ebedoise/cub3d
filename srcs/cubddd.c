#include "cub.h"

void	__init_game(t_game *g)
{
	g->w = 0;
	g->a = 0;
	g->s = 0;
	g->d = 0;
	g->right = 0;
	g->left = 0;
	g->esc = 0;
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	__init_textures(t_game *g)
{
	int	w;
	int	h;

	g->no_tex = mlx_xpm_file_to_image(g->vars.mlx, g->no, &w, &h);
	g->so_tex = mlx_xpm_file_to_image(g->vars.mlx, g->so, &w, &h);
	g->we_tex = mlx_xpm_file_to_image(g->vars.mlx, g->we, &w, &h);
	g->ea_tex = mlx_xpm_file_to_image(g->vars.mlx, g->ea, &w, &h);
}

int	__play(t_game g)
{
	g.vars.mlx = mlx_init();
	if (!g.vars.mlx)
		return (1);
	g.vars.win = mlx_new_window(g.vars.mlx, W_W, W_H, "cub3D");
	g.img.img = mlx_new_image(g.vars.mlx, 1280, 720);
	g.img.addr = mlx_get_data_addr(g.img.img, &g.img.bits_per_pixel, \
		&g.img.line_length, &g.img.endian);
	__init_textures(&g);
	__print_frame(&g);
	mlx_hook(g.vars.win, 2, 1L << 0, __key_press, &g);
	mlx_hook(g.vars.win, 3, 1L << 1, __key_release, &g);
	mlx_hook(g.vars.win, 17, 0, __close_window, &g);
	mlx_loop_hook(g.vars.mlx, __loop, &g);
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
		__init_game(&g);
		if (__file_checks(av[1], &g))
			return (1);
		if (__play(g))
		{
			__free_struct(&g);
			return (1);
		}
		__free_struct(&g);
	}
	return (0);
}
