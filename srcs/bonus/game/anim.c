#include "cub_bonus.h"

void	__print_vitals(t_game *g)
{
	if (g->anim <= 50)
		mlx_put_image_to_window(g->vars.mlx, g->vars.win, \
			g->vit[0].img, W_W - 178, W_H - 114);
	else if (g->anim <= 100)
		mlx_put_image_to_window(g->vars.mlx, g->vars.win, \
			g->vit[1].img, W_W - 178, W_H - 114);
	else if (g->anim <= 150)
		mlx_put_image_to_window(g->vars.mlx, g->vars.win, \
			g->vit[2].img, W_W - 178, W_H - 114);
	else if (g->anim <= 200)
	{
		mlx_put_image_to_window(g->vars.mlx, g->vars.win, \
			g->vit[3].img, W_W - 178, W_H - 114);
		if (g->anim == 200)
			g->anim = 0;
	}
}

void	__print_keys(t_game *g)
{
	mlx_string_put(g->vars.mlx, g->vars.win, 10, W_H - 10, 0x00FFFFFF, \
		"ESC             Quit");
	mlx_string_put(g->vars.mlx, g->vars.win, 10, W_H - 25, 0x00FFFFFF, \
		"[HOLD]Shift     Run");
	mlx_string_put(g->vars.mlx, g->vars.win, 10, W_H - 40, 0x00FFFFFF, \
		"E               Open/Close Doors");
	mlx_string_put(g->vars.mlx, g->vars.win, 10, W_H - 55, 0x00FFFFFF, \
		"<- ->           Move Camera");
	mlx_string_put(g->vars.mlx, g->vars.win, 10, W_H - 70, 0x00FFFFFF, \
		"W A S D         Move Player");
}
