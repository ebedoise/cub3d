#include "cub_bonus.h"

void	__init_game(t_game *g)
{
	g->w = 0;
	g->a = 0;
	g->s = 0;
	g->d = 0;
	g->right = 0;
	g->left = 0;
	g->shift = 0;
	g->esc = 0;
	g->mouse_x = W_W / 2;
	g->doors = 1;
	g->anim = 0;
}

int	__init_wall_textures(t_game *g)
{
	g->no_tex.img = mlx_xpm_file_to_image(g->vars.mlx, \
		g->no, &(g->no_tex.width), &(g->no_tex.height));
	if (!(g->no_tex.img))
		return (1);
	g->so_tex.img = mlx_xpm_file_to_image(g->vars.mlx, \
		g->so, &(g->so_tex.width), &(g->so_tex.height));
	if (!(g->so_tex.img))
		return (1);
	g->we_tex.img = mlx_xpm_file_to_image(g->vars.mlx, \
		g->we, &(g->we_tex.width), &(g->we_tex.height));
	if (!(g->we_tex.img))
		return (1);
	g->ea_tex.img = mlx_xpm_file_to_image(g->vars.mlx, \
		g->ea, &(g->ea_tex.width), &(g->ea_tex.height));
	if (!(g->ea_tex.img))
		return (1);
	g->no_tex.addr = mlx_get_data_addr(g->no_tex.img, &(g->no_tex.bpp), \
		&(g->no_tex.line_length), &(g->no_tex.endian));
	g->so_tex.addr = mlx_get_data_addr(g->so_tex.img, &(g->so_tex.bpp), \
		&(g->so_tex.line_length), &(g->so_tex.endian));
	g->we_tex.addr = mlx_get_data_addr(g->we_tex.img, &(g->we_tex.bpp), \
		&(g->we_tex.line_length), &(g->we_tex.endian));
	g->ea_tex.addr = mlx_get_data_addr(g->ea_tex.img, &(g->ea_tex.bpp), \
		&(g->ea_tex.line_length), &(g->ea_tex.endian));
	return (0);
}

int	__init_vitals(t_game *g)
{
	g->vit[0].img = mlx_xpm_file_to_image(g->vars.mlx, \
		"./textures/vitals1.xpm", &(g->vit[0].width), &(g->vit[0].height));
	if (!(g->vit[0].img))
		return (1);
	g->vit[1].img = mlx_xpm_file_to_image(g->vars.mlx, \
		"./textures/vitals2.xpm", &(g->vit[1].width), &(g->vit[1].height));
	if (!(g->vit[1].img))
		return (1);
	g->vit[2].img = mlx_xpm_file_to_image(g->vars.mlx, \
		"./textures/vitals3.xpm", &(g->vit[2].width), &(g->vit[2].height));
	if (!(g->vit[2].img))
		return (1);
	g->vit[3].img = mlx_xpm_file_to_image(g->vars.mlx, \
		"./textures/vitals4.xpm", &(g->vit[3].width), &(g->vit[3].height));
	if (!(g->vit[3].img))
		return (1);
	g->vit[0].addr = mlx_get_data_addr(g->vit[0].img, &(g->vit[0].bpp), \
		&(g->vit[0].line_length), &(g->vit[0].endian));
	g->vit[1].addr = mlx_get_data_addr(g->vit[1].img, &(g->vit[1].bpp), \
		&(g->vit[1].line_length), &(g->vit[1].endian));
	g->vit[2].addr = mlx_get_data_addr(g->vit[2].img, &(g->vit[2].bpp), \
		&(g->vit[2].line_length), &(g->vit[2].endian));
	g->vit[0].addr = mlx_get_data_addr(g->vit[0].img, &(g->vit[0].bpp), \
		&(g->vit[3].line_length), &(g->vit[3].endian));
	return (0);
}

int	__init_door_texture(t_game *g)
{
	g->door.img = mlx_xpm_file_to_image(g->vars.mlx, \
		"./textures/door.xpm", &(g->door.width), &(g->door.height));
	if (!(g->door.img))
		return (1);
	g->door.addr = mlx_get_data_addr(g->door.img, &(g->door.bpp), \
		&(g->door.line_length), &(g->door.endian));
	return (0);
}
