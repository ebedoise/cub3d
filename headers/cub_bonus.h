#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include "get_next_line.h"

# define W_H 720
# define W_W 1280

typedef struct s_coord
{
	int	x;
	int	y;
}		t_coord;

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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}		t_img;

typedef struct s_casting
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		tex_x;
	int		tex_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	wall_x;
	double	step;
	double	tex_pos;
}		t_casting;

typedef struct s_game
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		map_max;
	int		w;
	int		a;
	int		s;
	int		d;
	int		right;
	int		left;
	int		shift;
	int		mouse_x;
	int		esc;
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	t_rgb	f;
	t_rgb	c;
	t_vars	vars;
	t_img	img;
	t_img	no_tex;
	t_img	so_tex;
	t_img	we_tex;
	t_img	ea_tex;
}		t_game;

// event
void	__destroy(t_game *g);
void	__arrows(t_game *g, int u);
void	__left_mouse(t_game *g);
void	__right_mouse(t_game *g);

int		__close_window(t_game *g);
int		__loop(t_game *g);
int		__key_press(int keycode, t_game *g);
int		__key_release(int keycode, t_game *g);
int		__mouse_move(int x, int y, t_game *g);

// game
void	__print_frame(t_game *g);
void	__destroy(t_game *g);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	__print_view(t_game *g, t_casting *c, int x, int i);
void	__minimap(t_game *g);

// checks
int		__input(int ac, char **av, char **env);
int		__file_checks(char *str, t_game *g);
int		__data_checks(char *str, t_game *g);
int		__map_checks(t_game *g);
int		__cardinals(char *str, t_game *g);
int		__colors(char *str, t_game *g, char c, int i);
int		__check_sprites(t_game *g);

// utils
void	__free_split(char **strs);
void	__free_struct(t_game *g);

int		__strlen(char *str);
int		__strcmp(char *s1, char *s2);
int		__strncmp(char *s1, char *s2, int n);
int		__puterr(char *str);
int		__atoi(char *str, int *i);

char	*__strjoin(char *s1, char *s2);
char	*__strdup(char *s1);
char	*__strndup(char *s1, int n);
char	*__puterr_char(char *str);

char	**__split(char *s, char c);
char	**__free(char **array, int j);

#endif
