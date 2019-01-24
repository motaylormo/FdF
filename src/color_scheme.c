/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scheme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 12:16:42 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/10 17:38:45 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** If the file does not specify any colors, this color scheme is used.
** The gradient is standard across both highs and lows.
** For example, if the map has very high highs, but only shallow lows,
** then the highs will be vivid, and the lows faint.
*/

int			get_color_scale(t_window *window, t_point ***array)
{
	int	min_alt;
	int	max_alt;
	int	x;
	int	y;

	min_alt = 0;
	max_alt = 0;
	x = 0;
	while (x < window->rows)
	{
		y = 0;
		while (y < window->cols)
		{
			if (array[x][y]->alt < min_alt)
				min_alt = array[x][y]->alt;
			if (array[x][y]->alt > max_alt)
				max_alt = array[x][y]->alt;
			y++;
		}
		x++;
	}
	return ((max_alt >= abs(min_alt)) ? max_alt : abs(min_alt));
}

t_point		***add_color_scheme(t_window *window, t_point ***array,
			int color_scale)
{
	t_gradient	*highs_grad;
	t_gradient	*lows_grad;
	int			x;
	int			y;

	highs_grad = make_gradient(NEUT_COLOR, HIGHS_COLOR, color_scale);
	lows_grad = make_gradient(NEUT_COLOR, LOWS_COLOR, color_scale);
	x = 0;
	while (x < window->rows)
	{
		y = 0;
		while (y < window->cols)
		{
			if (array[x][y]->alt == 0)
				array[x][y]->color = NEUT_COLOR;
			else
				array[x][y]->color = color_step((array[x][y]->alt > 0) ?
						highs_grad : lows_grad, abs(array[x][y]->alt));
			y++;
		}
		x++;
	}
	free_gradient(&highs_grad);
	free_gradient(&lows_grad);
	return (array);
}
