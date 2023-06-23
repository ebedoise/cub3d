/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: embedois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:28:47 by embedois          #+#    #+#             */
/*   Updated: 2023/02/08 15:28:48 by embedois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	__destroy(t_game *g)
{
	__free_struct(g);
	mlx_destroy_window(g->vars.mlx, g->vars.win);
	mlx_destroy_display(g->vars.mlx);
	free(g->vars.mlx);
	exit(0);
}

int	__close_window(t_game *g)
{
	__destroy(g);
	exit(0);
	return (0);
}
