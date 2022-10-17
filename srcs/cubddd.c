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

int	__key_hook(int keycode, t_game *g)
{
	if (keycode == 65307)
		__destroy(g);
	return (0);
}

int	__play(char *str, t_game g)
{
	(void)str;
	g.vars.mlx = mlx_init();
	if (!g.vars.mlx)
		return (1);
	g.vars.win = mlx_new_window(g.vars.mlx, 1280, 720, "cub3D");
	mlx_key_hook(g.vars.win, __key_hook, &g);
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
		__free_split(g.map);
		free(g.no);
		free(g.so);
		free(g.we);
		free(g.ea);
		//if (__play(av[1], g))
		//	return (1);
	}
	return (0);
}
