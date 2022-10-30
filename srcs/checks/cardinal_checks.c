#include "cub.h"

int	__check_sprites(t_game *g)
{
	int	i;

	i = open(g->no, O_RDONLY);
	if (i == -1)
		return (1);
	close(i);
	i = open(g->so, O_RDONLY);
	if (i == -1)
		return (1);
	close(i);
	i = open(g->we, O_RDONLY);
	if (i == -1)
		return (1);
	close(i);
	i = open(g->ea, O_RDONLY);
	if (i == -1)
		return (1);
	close(i);
	return (0);
}

int	__cardinals(char *str, t_game *g)
{
	char	**strs;

	strs = __split(str, ' ');
	if (!strs)
		return (1);
	if (!strs[1] || strs[2])
	{
		__free_split(strs);
		return (1);
	}
	if ((__strcmp(strs[0], "NO") == 0 && g->no != NULL)
		|| (__strcmp(strs[0], "SO") == 0 && g->so != NULL)
		|| (__strcmp(strs[0], "WE") == 0 && g->we != NULL)
		|| (__strcmp(strs[0], "EA") == 0 && g->ea != NULL))
		return (1);
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

int	__colors(char *str, t_game *g, char c, int i)
{
	if (c == 'f')
	{
		g->f.r = __atoi(str, &i);
		if (str[i++] != ',' || g->f.r < 0 || g->f.r > 255)
			return (1);
		g->f.g = __atoi(str, &i);
		if (str[i++] != ',' || g->f.g < 0 || g->f.g > 255)
			return (1);
		g->f.b = __atoi(str, &i);
		if (str[i] || g->f.b < 0 || g->f.b > 255)
			return (1);
	}
	else if (c == 'c')
	{
		g->c.r = __atoi(str, &i);
		if (str[i++] != ',' || g->c.r < 0 || g->c.r > 255)
			return (1);
		g->c.g = __atoi(str, &i);
		if (str[i++] != ',' || g->c.g < 0 || g->c.g > 255)
			return (1);
		g->c.b = __atoi(str, &i);
		if (str[i] || g->c.b < 0 || g->c.b > 255)
			return (1);
	}
	return (0);
}
