/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:30:36 by mtaylor           #+#    #+#             */
/*   Updated: 2019/01/21 13:22:05 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_WIDTH 1000

static void		img_pixel_put(t_image *img, int x, int y, int color)
{
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		*(int *)(img->data + (int)((x + y * img->width) * img->bpp)) = color;
	}
}

/*
** Draws a "x centric" line
** (ie. the kind you were taught in math class)
** The y is iterated by the slope, while the x is iterated by 1.
*/

static t_image	*draw_x_line(t_image *img, t_xy *start, t_xy *end)
{
	int			x;
	double		y;
	double		slope;
	t_gradient	*gradient;

	x = start->x;
	y = start->y;
	gradient = make_gradient(start->color, end->color, end->x - start->x);
	slope = ((double)start->y - (double)end->y) /
			((double)start->x - (double)end->x);
	while (x <= end->x)
	{
		img_pixel_put(img, x, y, gradient->curr_color);
		x++;
		y += slope;
		gradient = iterate_color(gradient);
	}
	free_gradient(&gradient);
	return (img);
}

/*
** Draws a "y centric" line
** The x is iterated by the slope, while the y is iterated by 1.
** Vertical lines can also be drawn this way.
*/

static t_image	*draw_y_line(t_image *img, t_xy *start, t_xy *end)
{
	double		x;
	int			y;
	double		slope;
	t_gradient	*gradient;

	x = start->x;
	y = start->y;
	gradient = make_gradient(start->color, end->color, end->y - start->y);
	slope = ((double)start->x - (double)end->x) /
			((double)start->y - (double)end->y);
	while (y <= end->y)
	{
		img_pixel_put(img, x, y, gradient->curr_color);
		x += slope;
		y++;
		gradient = iterate_color(gradient);
	}
	free_gradient(&gradient);
	return (img);
}

/*
** Figures out what the slope of the line is,
** and sends it to be drawn by vert_line, x_line, or y_line accordingly.
** Swaps the "start" and "end" xy if needed.
*/

t_image			*put_line(t_image *img, t_xy *start, t_xy *end)
{
	if (start->x == end->x || abs(start->y - end->y) > abs(start->x - end->x))
	{
		img = draw_y_line(img, (start->y <= end->y) ? start : end,
								(start->y < end->y) ? end : start);
	}
	else
	{
		img = draw_x_line(img, (start->x <= end->x) ? start : end,
								(start->x < end->x) ? end : start);
	}
	free_xy(&start);
	free_xy(&end);
	return (img);
}
