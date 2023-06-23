/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: embedois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:26:04 by embedois          #+#    #+#             */
/*   Updated: 2023/02/08 15:26:06 by embedois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
