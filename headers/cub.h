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

# define PI 3.1415926
# define windowH 720
# define windowW 1280

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

typedef struct	s_img
{
	void    *img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_img;

typedef struct s_game
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int	timer;
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;
	t_rgb	f;
	t_rgb	c;
	t_vars	vars;
	t_img	img;
}		t_game;

//checks
int	__input(int ac, char **av, char **env);
int	__file_checks(char *str, t_game *g);
int	__data_checks(char *str, t_game *g);
int	__map_checks(t_game *g);
int	__cardinals(char *str, t_game *g);
int	__colors(char *str, t_game *g, char c);

// utils
void	__free_split(char **strs);

int	__strlen(char *str);
int	__strcmp(char *s1, char *s2);
int	__strncmp(char *s1, char *s2, int n);
int	__puterr(char *str);
int	__atoi(char *str, int *i);

char	*__strjoin(char *s1, char *s2);
char	*__strdup(char *s1);
char	*__strndup(char *s1, int n);

char	**__split(char *str, char *charset);

#endif
