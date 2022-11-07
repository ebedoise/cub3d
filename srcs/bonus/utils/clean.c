#include "cub_bonus.h"

void	__free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**__free(char **array, int j)
{
	while (j >= 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
	return (NULL);
}

void	__free_struct(t_game *g)
{
	__free_split(g->map);
	free(g->no);
	free(g->so);
	free(g->we);
	free(g->ea);
	mlx_destroy_image(g->vars.mlx, g->no_tex.img);
	mlx_destroy_image(g->vars.mlx, g->so_tex.img);
	mlx_destroy_image(g->vars.mlx, g->we_tex.img);
	mlx_destroy_image(g->vars.mlx, g->ea_tex.img);
}
