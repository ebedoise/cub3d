#include "cub.h"

char	*init_file(char *str)
{
	char	*buf;
	char	*tmp;
	int	fd;

	buf = malloc(sizeof(char));
	if (!buf)
		return (NULL);//puterr
	buf[0] = '\0';
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (NULL);//puterr
	tmp = get_next_line(fd);
	while (tmp)
	{
		buf = __strjoin(buf, tmp);
		if (!buf)
			return (NULL);//puterr
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
			break;
		}
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			i++;
	}
	return (save);
}

int	__data_checks(char *str, t_game *g)
{
	(void)str;
	(void)g;

	//bzero
	//split str \n
	//NO SO WE EA F C assign
	//if one is == NULL err
	//check open NO SO WE EA
	//check valid colors F C
	return (0);
}

int	__file_checks(char *str, t_game *g)
{
	char	*buf;
	int	start_map;

	buf = init_file(str);
	if (!buf)
		return (1);
	start_map = __start_map(buf);
	g->map = __strdup(buf + start_map);
	buf = __strndup(buf, start_map);
	printf("%s", buf);
	if (__data_checks(buf, g))
	{
		free(buf);
		return (1);//puterr
	}
	free(buf);
	return (0);
}

//while exist
//check map
//1 next at least 1 0/1/start
//0 next to 0/1/start only
//N,S,E,W next to 0/1 only
//only 1 start (N, S, E, W)
//no empty lines
