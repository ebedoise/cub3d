#include "cub_bonus.h"

int	__directory(char *av)
{
	int	ret;

	ret = open(av, O_DIRECTORY);
	if (ret != -1)
	{
		close(ret);
		return (1);
	}
	return (0);
}

int	__check_empty(int fd)
{
	char	buf[2];
	int		c;

	c = read(fd, buf, 1);
	if (c == -1)
		return (0);
	if (!buf[0])
		return (0);
	return (1);
}

int	__check_file(char *av)
{
	int	ret;

	ret = open(av, O_RDONLY);
	if (ret == -1)
		return (__puterr("Cannot open the file"));
	if (!__check_empty(ret))
	{
		close(ret);
		return (__puterr("Empty file"));
	}
	close(ret);
	return (0);
}

int	__input(int ac, char **av, char **env)
{
	if (!env[0])
		return (__puterr("No environment"));
	else if (ac != 2)
		return (__puterr("Wrong number of arguments"));
	else if (__strlen(av[1]) <= 4
		|| __strcmp(av[1] + __strlen(av[1]) - 4, ".cub"))
		return (__puterr("Invalide file name (something.cub needed)"));
	else if (__directory(av[1]))
		return (__puterr("Is a directory"));
	else if (__check_file(av[1]))
		return (1);
	return (0);
}
