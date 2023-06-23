/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: embedois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:26:48 by embedois          #+#    #+#             */
/*   Updated: 2023/02/08 15:26:50 by embedois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*__puterr_char(char *str)
{
	int	oui;

	oui = write(2, "Error\n", 6);
	while (*str)
		oui = write(2, str++, 1);
	oui = write(2, "\n", 1);
	(void)oui;
	return (NULL);
}
