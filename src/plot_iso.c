/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_coords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:24:59 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/17 15:32:05 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** The is taken from the FdF Cookbook,
** but fixed (+ and - inverted) so as not to be backwards
*/

static t_point	*iso_right(t_point *p, int x, int y)
{
	int		z;

	z = p->alt;
	p->x = (x + y) * cos(ANGLE);
	p->y = ((x - y) * sin(ANGLE)) - z;
	return (p);
}

t_point			***set_iso_coords(t_window *window, t_point ***array)
{
	int		x;
	int		y;

	x = 0;
	while (x < window->rows)
	{
		y = 0;
		while (y < window->cols)
		{
			array[x][y] = iso_right(array[x][y], x, y);
			y++;
		}
		x++;
	}
	array = center(window, array);
	return (array);
}
