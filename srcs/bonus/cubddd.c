/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubddd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: embedois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:27:59 by embedois          #+#    #+#             */
/*   Updated: 2023/02/09 13:08:09 by embedois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

//mlx_mouse_hide(g.vars.mlx, g.vars.win); fct leaks
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
	if (__init_door_texture(&g))
		return (__puterr("Can't load textures"));
	if (__init_vitals(&g))
		return (__puterr("Can't load textures"));
	__arrows(&g, 0);
	__print_frame(&g);
	mlx_mouse_move(g.vars.mlx, g.vars.win, W_W / 2, W_H / 2);
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
		{
			__free_struct1(&g);
			return (1);
		}
		if (__play(g))
			__destroy(&g);
		__free_struct(&g);
	}
	return (0);
}
