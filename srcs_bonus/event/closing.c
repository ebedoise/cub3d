#include "cub_bonus.h"

void	__free_map(t_game *g)
{
	int	i;

	i = 0;
	while (g->map[i])
		free(g->map[i++]);
	free(g->map);
	free(g->no);
	free(g->so);
	free(g->we);
	free(g->ea);
}

void	__destroy(t_game *g)
{
	//mlx_clear_window (g->vars.mlx, g->vars.win);
	mlx_destroy_window(g->vars.mlx, g->vars.win);
	mlx_destroy_display(g->vars.mlx);
	free(g->img.img);
	//free(g->img.addr);
	free(g->vars.mlx);
	__free_map(g);
	exit(0);
}

int	__close_window(t_game *g)
{
	__destroy(g);
	exit(0);
	return (0);
}
