#include "cub.h"

// add checks for the textures when implemented
// if multiple NO SO EA WE ??
int	__cardinals(char *str, t_game *g)
{
	char	**strs;

	strs = __split(str, " ");
	if (!strs)
		return (1);
	if (!strs[1] || strs[2])
	{
		__free_split(strs);
		return (1);
	}
	if (__strcmp(strs[0], "NO") == 0)
		g->no = __strdup(strs[1]);
	else if (__strcmp(strs[0], "SO") == 0)
		g->so = __strdup(strs[1]);
	else if (__strcmp(strs[0], "WE") == 0)
		g->we = __strdup(strs[1]);
	else if (__strcmp(strs[0], "EA") == 0)
		g->ea = __strdup(strs[1]);
	__free_split(strs);
	return (0);
}

int	__colors(char *str, t_game *g, char c)
{
	(void)str;
	if (c == 'f')
	{
		g->f.r = 1;
		g->f.g = 1;
		g->f.b = 1;
	}
	else if (c == 'c')
	{
		g->c.r = 1;
		g->c.g = 1;
		g->c.b = 1;
	}
	return (0);
}
