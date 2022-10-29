#include "cub.h"

char	*init_file(char *str)
{
	char	*buf;
	char	*tmp;
	int		fd;

	buf = malloc(sizeof(char));
	if (!buf)
		return (__puterr_char("Malloc issue"));
	buf[0] = '\0';
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (__puterr_char("Malloc issue"));
	tmp = get_next_line(fd);
	while (tmp)
	{
		buf = __strjoin(buf, tmp);
		if (!buf)
			return (__puterr_char("Malloc issue"));
		free(tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	return (buf);
}

int	first_line_map(char *str)
{
	int	i;
	int	one;

	i = 0;
	one = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != '1' && str[i] != ' ')
			return (0);
		if (str[i] == '1')
			one++;
		i++;
	}
	if (!one)
		return (0);
	return (1);
}

int	__start_map(char *str)
{
	int	i;
	int	save;

	i = 0;
	save = 0;
	while (str[i])
	{
		if (first_line_map(str + i))
		{
			save = i;
			break ;
		}
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			i++;
	}
	return (save);
}

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

int	__file_checks(char *str, t_game *g)
{
	char	*buf;
	char	*map_tmp;
	int		start_map;

	buf = init_file(str);
	if (!buf)
		return (1);
	start_map = __start_map(buf);
	//check empty lines map ?
	map_tmp = __strdup(buf + start_map);
	g->map = __split(map_tmp, "\n");
	free(map_tmp);
	if (!g->map)
		return (1);
	buf = __strndup(buf, start_map);
	if (__data_checks(buf, g))
		return (1);//puterr exemple map ?
	if (__check_sprites(g))
		return (__puterr("Invalid textures"));
	if (__map_checks(g))
		return (__puterr("Wrong map format"));
	return (0);
}
