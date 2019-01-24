/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:29:07 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/17 17:06:44 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Takes the minimum x and minimum y (if they're less than 0)
** and adds their absolute values to every point of the image
** so there's no neg numbers and everything appears
*/

static void	get_offsets(t_window *window, t_point ***array,
			double *x_offset, double *y_offset)
{
	int	x;
	int	y;

	x = 0;
	while (x < window->rows)
	{
		y = 0;
		while (y < window->cols)
		{
			if (array[x][y]->x < *x_offset)
				*x_offset = array[x][y]->x;
			if (array[x][y]->y < *y_offset)
				*y_offset = array[x][y]->y;
			y++;
		}
		x++;
	}
	*x_offset = fabs(*x_offset);
	*y_offset = fabs(*y_offset);
}

t_point		***center(t_window *window, t_point ***array)
{
	double	x_offset;
	double	y_offset;
	int		x;
	int		y;

	x_offset = 0;
	y_offset = 0;
	get_offsets(window, array, &x_offset, &y_offset);
	x = 0;
	while (x < window->rows)
	{
		y = 0;
		while (y < window->cols)
		{
			array[x][y]->x += x_offset;
			array[x][y]->y += y_offset;
			y++;
		}
		x++;
	}
	return (array);
}
