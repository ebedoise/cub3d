#ifndef CUB_H
# define CUB_H

# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include "get_next_line.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}		t_vars;

typedef struct s_game
{
	char	**map;
	t_vars	vars;
}		t_game;

//checks
int __input(int ac, char **av, char **env);

// utils
int	__strlen(char *str);
int	__strcmp(char *s1, char *s2);
int	__puterr(char *str);

#endif
