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
			if (__valid(g->map[i][j]) && g->map[i][j] != ' ')
				return (__puterr("Bad character in map"));//puterr bad character in map
			else if ((g->map[i][j] == '0' || g->map[i][j] == 'N'
				|| g->map[i][j] == 'S' || g->map[i][j] == 'W'
				|| g->map[i][j] == 'E') && __zero_checks(g, i, j))
				return (__puterr("Map unclosed"));//puterr invalid map
			else if ((g->map[i][j] == 'N' || g->map[i][j] == 'S'
				|| g->map[i][j] == 'W' || g->map[i][j] == 'E'))
			{
				if (pos)
					return (__puterr("Multiple starting position"));
				pos++;
				g->pos_x = i;
				g->pos_y = j;
				if (g->map[i][j] == 'N')
				{
					g->dir_x = 0;
					g->dir_y = 1;
				}
				else if (g->map[i][j] == 'E')
				{
					g->dir_x = 1;
					g->dir_y = 0;
				}
				else if (g->map[i][j] == 'S')
				{
					g->dir_x = 0;
					g->dir_y = -1;
				}
				else if (g->map[i][j] == 'W')
				{
					g->dir_x = -1;
					g->dir_y = 0;
				}
			}
			j++;
		}
		i++;
	}
	if (!pos)
		return (__puterr("No starting position"));
	return (0);
}
