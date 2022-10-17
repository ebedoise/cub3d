#include "cub.h"

int	__valid(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (1);
	return (0);
}

int	__zero_checks(t_game *g, int i, int j)
{
	if (i == 0 || !g->map[i + 1] || j == 0 || j == __strlen(g->map[i]) - 1)
		return (1);//puterr border
	if (__valid(g->map[i - 1][j - 1]) || __valid(g->map[i + 1][j - 1])
		|| __valid(g->map[i - 1][j + 1]) || __valid(g->map[i][j - 1])
		|| __valid(g->map[i + 1][j + 1]) || __valid(g->map[i][j + 1])
		|| __valid(g->map[i - 1][j]) || __valid(g->map[i + 1][j]))
		return (1);//puterr area
	return (0);
}

int	__map_checks(t_game *g)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	pos = 0;
	while (g->map[i])
	{
		j = 0;
		while (g->map[i][j])
		{
			if ((g->map[i][j] == '0' || g->map[i][j] == 'N'
				|| g->map[i][j] == 'S' || g->map[i][j] == 'W'
				|| g->map[i][j] == 'E') && __zero_checks(g, i, j))
				return (1);//puterr invalid map
			j++;
		}
		i++;
	}
	return (0);
}

//while exist
//check map
//1 next at least 1 0/1/start
//0 next to 0/1/start only
//N,S,E,W next to 0/1 only
//only 1 start (N, S, E, W)
//no empty lines
