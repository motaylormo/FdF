/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 11:31:54 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/21 13:30:16 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_image	*link_gridpoints(t_image *img, t_point *a, t_point *b)
{
	int a_x;
	int a_y;
	int b_x;
	int b_y;

	a_x = (a->x * img->scale) + 0.5 + MARGIN;
	a_y = (a->y * img->scale) + 0.5 + MARGIN;
	b_x = (b->x * img->scale) + 0.5 + MARGIN;
	b_y = (b->y * img->scale) + 0.5 + MARGIN;
	return (put_line(img, xy(a_x, a_y, a->color),
							xy(b_x, b_y, b->color)));
}

t_image			*draw_wireframe(t_image *img, t_window *window,
				t_point ***array)
{
	int x;
	int y;

	x = 0;
	while (x < window->rows)
	{
		y = 0;
		while (y < window->cols)
		{
			if (y + 1 < window->cols)
				img = link_gridpoints(img, array[x][y], array[x][y + 1]);
			if (x + 1 < window->rows)
				img = link_gridpoints(img, array[x][y], array[x + 1][y]);
			y++;
		}
		x++;
	}
	return (img);
}
