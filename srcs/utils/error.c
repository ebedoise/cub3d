#include "cub.h"

//oui for flags in e2z3
int	__puterr(char *str)
{
	int	oui;

	oui = write(2, "Error\n", 6);
	while (*str)
		oui = write(2, str++, 1);
	oui = write(2, "\n", 1);
	(void)oui;
	return (1);
}
