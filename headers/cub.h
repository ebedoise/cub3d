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

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}		t_vars;

typedef struct s_game
{
	char	*map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	double	start_rad;
	double	start_x;
	double	start_y;
	t_rgb	f;
	t_rgb	c;
	t_vars	vars;
}		t_game;

//checks
int	__input(int ac, char **av, char **env);
int	__file_checks(char *str, t_game *g);
int	__data_checks(char *str, t_game *g);
int	__cardinals(char *str, t_game *g);
int	__colors(char *str, t_game *g, char c);

// utils
void	__free_split(char **strs);

int	__strlen(char *str);
int	__strcmp(char *s1, char *s2);
int	__strncmp(char *s1, char *s2, int n);
int	__puterr(char *str);

char	*__strjoin(char *s1, char *s2);
char	*__strdup(char *s1);
char	*__strndup(char *s1, int n);

char	**__split(char *str, char *charset);

#endif
