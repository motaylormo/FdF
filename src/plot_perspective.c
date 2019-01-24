/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:22:53 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/21 14:41:56 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	*perspective(t_point *p, int tz)
{
	double	z;

	z = p->alt - tz;
	p->x /= z;
	p->y /= z;
	return (p);
}

static t_point	*rotate(t_point *p, double angle)
{
	double	x;
	double	y;

	x = p->x;
	y = p->y;
	p->x = (x * cos(angle)) + (y * -sin(angle));
	p->y = (x * sin(angle)) + (y * cos(angle));
	return (p);
}

static int		get_z_transformation(t_window *window, t_point ***array)
{
	int		x;
	int		y;
	int		max_z;
	int		min_z;
	int		d;

	max_z = array[0][0]->alt;
	min_z = array[0][0]->alt;
	x = 0;
	while (x < window->rows)
	{
		y = 0;
		while (y < window->cols)
		{
			if (array[x][y]->alt > max_z)
				max_z = array[x][y]->alt;
			if (array[x][y]->alt < min_z)
				min_z = array[x][y]->alt;
			y++;
		}
		x++;
	}
	d = (window->rows > window->cols) ? window->rows : window->cols;
	return ((max_z - min_z) + d);
}

t_point			***set_perspective_coords(t_window *window, t_point ***array)
{
	int		x;
	int		y;
	int		tz;

	tz = get_z_transformation(window, array);
	x = 0;
	while (x < window->rows)
	{
		y = 0;
		while (y < window->cols)
		{
			array[x][y]->x = window->rows - x;
			array[x][y]->y = y;
			array[x][y] = rotate(array[x][y], PER_ANGLE);
			array[x][y] = perspective(array[x][y], tz);
			y++;
		}
		x++;
	}
	array = center(window, array);
	return (array);
}
