#include "cub.h"

int	__puterr(char *str)
{
	write(2, "Error\n", 6);
	while (*str)
		write(2, str++, 1);
	write(2, "\n", 1);
	return (1);
}
