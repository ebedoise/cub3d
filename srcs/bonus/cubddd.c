#include "cub_bonus.h"

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

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	__init_wall_textures(t_game *g)
{
	g->no_tex.img = mlx_xpm_file_to_image(g->vars.mlx, \
		g->no, &(g->no_tex.width), &(g->no_tex.height));
	if (!(g->no_tex.img))
		return (1);
	g->so_tex.img = mlx_xpm_file_to_image(g->vars.mlx, \
		g->so, &(g->so_tex.width), &(g->so_tex.height));
	if (!(g->so_tex.img))
		return (1);
	g->we_tex.img = mlx_xpm_file_to_image(g->vars.mlx, \
		g->we, &(g->we_tex.width), &(g->we_tex.height));
	if (!(g->we_tex.img))
		return (1);
	g->ea_tex.img = mlx_xpm_file_to_image(g->vars.mlx, \
		g->ea, &(g->ea_tex.width), &(g->ea_tex.height));
	if (!(g->ea_tex.img))
		return (1);
	g->no_tex.addr = mlx_get_data_addr(g->no_tex.img, &(g->no_tex.bpp), \
		&(g->no_tex.line_length), &(g->no_tex.endian));
	g->so_tex.addr = mlx_get_data_addr(g->so_tex.img, &(g->so_tex.bpp), \
		&(g->so_tex.line_length), &(g->so_tex.endian));
	g->we_tex.addr = mlx_get_data_addr(g->we_tex.img, &(g->we_tex.bpp), \
		&(g->we_tex.line_length), &(g->we_tex.endian));
	g->ea_tex.addr = mlx_get_data_addr(g->ea_tex.img, &(g->ea_tex.bpp), \
		&(g->ea_tex.line_length), &(g->ea_tex.endian));
	////////////////////////////
	g->sprite.img = mlx_xpm_file_to_image(g->vars.mlx, \
		"./textures/chainsaw.xpm", &(g->sprite.width), &(g->sprite.height));
	if (!(g->sprite.img))
		return (1);
	g->sprite.addr = mlx_get_data_addr(g->sprite.img, &(g->sprite.bpp), \
		&(g->sprite.line_length), &(g->sprite.endian));
	return (0);
}

int	__play(t_game g)
{
	g.vars.mlx = mlx_init();
	if (!g.vars.mlx)
		return (1);
	g.vars.win = mlx_new_window(g.vars.mlx, W_W, W_H, "cub3D");
	g.img.img = mlx_new_image(g.vars.mlx, 1280, 720);
	g.img.addr = mlx_get_data_addr(g.img.img, &g.img.bpp, \
		&g.img.line_length, &g.img.endian);
	if (__init_wall_textures(&g))
		return (__puterr("Can't load textures"));
	__arrows(&g, 0);
	__print_frame(&g);
	mlx_mouse_move(g.vars.mlx, g.vars.win, W_W / 2, W_H / 2);
	//mlx_mouse_hide(g.vars.mlx, g.vars.win);
	mlx_hook(g.vars.win, 2, 1L << 0, __key_press, &g);
	mlx_hook(g.vars.win, 3, 1L << 1, __key_release, &g);
	mlx_hook(g.vars.win, 6, 1L << 6, __mouse_move, &g);
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
